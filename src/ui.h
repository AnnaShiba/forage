#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "binding.h"
#include "point.h"
#include "ui_style.h"

class UIComponent
{
protected:
    Rect _rect;
    bool _hidden = false;

public:
    UIComponent( const Rect & dimensions );
    virtual ~UIComponent() = default;

    virtual void update( float deltaTime ) = 0;
    virtual void render() = 0;

    virtual void handleClickEvent( const Point & click, int modes ) {}

    bool isHidden() const
    {
        return _hidden;
    }

    void setHidden( bool isHidden )
    {
        _hidden = isHidden;
    }

    const Rect & getRect() const
    {
        return _rect;
    }
};

class UIContainer : public UIComponent
{
protected:
    std::vector<std::shared_ptr<UIComponent> > _items;

public:
    UIContainer( const Rect & dimensions );

    virtual void update( float deltaTime );
    virtual void render();
    virtual void handleClickEvent( const Point & click, int modes );

    void addElement( std::shared_ptr<UIComponent> element );
    virtual std::shared_ptr<UIComponent> getElement( const Point & position );
    void updateRect();
};

// A basic text label element
class Label : public UIComponent
{
public:
    Label( const Point & position, const std::string & text );
    Label( const Point & position, const std::string & text, StandardFont font, StandardColor color );

    void setColor( StandardColor color );
    virtual void setText( const std::string & text );

    virtual void update( float deltaTime ) override {}
    virtual void render() override;

protected:
    std::string _text;
    StandardFont _font = StandardFont::REGULAR;
    StandardColor _color = StandardColor::WHITE;
};

class Button : public UIComponent
{
    std::string _label;
    Style _style;
    bool _isHovered = false;
    bool _isPressed = false;

public:
    Button( int x, int y, int width, int height, const std::string & label );
    Button( const Rect & dimensions, const std::string & label, const Style & style );
    Button( const Point & position, int width, int height, const std::string & label, const Style & style );
    virtual ~Button() = default;

    void update( float deltaTime ) override;
    void render() override;

    void setPressed( bool value );
    void setHovered( bool value );
    void setStyle( const Style & style );
    void setLabel( const std::string & label );
};

class ProgressBar : public UIComponent
{
    Style _style;

public:
    ValueComponent _binding;

    ProgressBar( const Rect & dimensions, ValueBinding binding );
    ProgressBar( const Rect & dimensions, ValueBinding binding, const Style & style );

    void setStyle( const Style & style );
    virtual void update( float deltaTime ) override {}
    virtual void render() override;
};

class CenteringLabel : public Label
{
    Point _expectedSize;

public:
    CenteringLabel( const Point & position, const std::string & text, int width );
    CenteringLabel( const Rect & dimensions, const std::string & text );
    CenteringLabel( const Rect & dimensions, const std::string & text, StandardFont font, StandardColor color );
    virtual void render() override;
};

// A basic menu element
class Menu : public UIComponent
{
public:
    Menu();

    void addElement( UIComponent * element );

    virtual void render();

private:
    std::vector<UIComponent *> _elements;
    Point _spacing;
};

class Window : public UIComponent
{
public:
    Window( Rect rect, const std::string & title );
    ~Window();

    void update( float deltaTime );
    void render();

    void setStyle( const Style & style );
    void addComponent( std::shared_ptr<UIComponent> component );

    std::shared_ptr<UIComponent> getElement( const Point & click );

private:
    Style _style;
    std::string _title;
    std::vector<std::shared_ptr<UIComponent> > _components;
};
