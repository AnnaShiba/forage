#pragma once
#include "binding.h"
#include "character_class.h"
#include "point.h"
#include "spell.h"

namespace RPG
{
    enum class AttackSource
    {
        PHYSICAL,
        MAGIC
    };

    enum class CharacterPreset
    {
        MELEE,
        AGILE,
        WIZARD,
        MONSTER
    };

    enum class CharacterAttributes
    {
        HEALTH,
        LEVEL,

        STRENGTH,
        DEXTERITY,
        AGILITY,
        CONSTITUTION,
        INTELLIGENCE,
        WILLPOWER,
        CHARISMA,

        CLOSE_COMBAT,
        RANGED_COMBAT,
        DODGE,
        BLOCK,
        STEALTH,

        LIFE,
        ARCANA,
        NATURE,
        CHAOS,
        DEATH,

        MAGIC_FIRE,
        MAGIC_WATER,
        MAGIC_AIR,
        MAGIC_EARTH,
        MAGIC_MENTAL,
        MAGIC_DIVINITY
    };

    class Character : protected Unit
    {
        Stats stats;
        int skills[Skills::INVALID_SKILL] = { 0 };
        int level = 0;

        static int lastID;

    public:
        Character();
        Character( CharacterPreset preset );

        CharacterClass getClass() const;

        int getId() const
        {
            return id;
        }

        int getInitiative() const
        {
            return 100 + ( stats.agility + stats.dexterity ) / 2;
        }

        int getAttackCount( bool isRanged ) const
        {
            const int statValue = isRanged ? stats.strength + stats.agility : stats.agility + stats.dexterity;
            const int count = statValue / 33;
            return ( count > 0 ) ? count : 1;
        }

        int getAttackDamage( bool isRanged ) const
        {
            const int statValue = isRanged ? ( stats.strength + stats.dexterity ) / 2 : stats.strength;
            return 1 + statValue / 10;
        }

        int getMagicDamage() const
        {
            return 1 + ( stats.intelligence + stats.willpower ) / 20;
        }

        double calcMagicSuccessChance( Spell spell, int power ) const
        {
            const int difficulty = spell.level * 20 + power * 10;
            const int skill = skills[Skills::LIFE]; //+ getRealmSkill( spell.realm );
            return skill / difficulty;
        }

        int getCurrentHealth() const
        {
            return currentHealth;
        }

        int getMaxHealth() const
        {
            return 1 + ( stats.constitution / 6 + 1 ) * level;
        }

        bool isDead() const
        {
            return currentHealth <= 0;
        }

        bool recieveDamage( AttackSource source, int damage )
        {
            currentHealth -= damage;
            if ( currentHealth < 0 ) {
                currentHealth = 0;
            }
            return isDead();
        }

        bool recieveHealing( int amount )
        {
            currentHealth += amount;

            const int max = getMaxHealth();
            if ( currentHealth > max ) {
                currentHealth = max;
                return true;
            }
            return false;
        }

        static std::string GetSkillName( CharacterAttributes skill );

        ValueBinding getBinding( CharacterAttributes attribute );
    };

    using CharacterRef = std::reference_wrapper<Character>;
}
