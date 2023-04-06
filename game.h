#pragma once
#include <iostream>
#include <vector>

#include "base_game.h"
#include "wave_function.h"

class Game : public BaseGame
{
    bool _isRunning = false;

    // Add any additional game state variables or components here
    WaveMap _map;

public:
    Game()
        : _map( 16 )
    {}
    ~Game() {
        cleanup();
    }

    bool init();
    void handleEvents();
    void update( float deltaTime );
    void render() override;
    void run();
    void realtimeLoop();
    void cleanup();
};
