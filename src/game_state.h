#pragma once

#include "map.h"
#include "rpg_arena.h"
#include "wave_function.h"
#include "rng.h"
#include <array>

struct GameState
{
    WaveMap map;
    RPG::Force playerForce;
    RPG::Force otherForce;
    std::vector<RPG::Character> units;

    GameState() : map(32) {
        const std::array positions { RPG::Force::FRONT, RPG::Force::SIDE, RPG::Force::CENTER, RPG::Force::BACK };

        for ( int i = 0; i < 8; ++i ) {
            const int maximum = static_cast<int>( RPG::CharacterPreset::MONSTER );
            units.emplace_back( static_cast<RPG::CharacterPreset>( RandomGenerator::Get().next( 0, maximum ) ) );

            if ( i < 4 ) {
                playerForce.add( units[i], false, positions[i % 4] );
            }
            else {
                otherForce.add( units[i], true, positions[i % 4] );
            }
        }
    }
};
