/* ---------------------------------------------------------------------------
** Team Bear King
** © 2015 DigiPen Institute of Technology, All Rights Reserved.
**
** StateArrayConfig.h
**
** Author:
** - Jordan Ellis - j.ellis@digipen.edu
** - Joshua Shlemmer - joshua.shlemmer@digipen.edu
**
** -------------------------------------------------------------------------*/
#pragma once

#include <functional>
#include "Entity.h"
#include "AITargetFinder.h"
#include "PlayerSystem.h"
#include "Abilities.h"
#include "PlayerComponent.h"

namespace Ursine
{
    // All state types that are possible
    #define REGISTER_STATE(x, y) STATE_ ## x,

    // Build an enum full of our state types
    enum StateType
    {
        #include "RegisterStates.h"

        STATE_NUM
    };

    #undef REGISTER_STATE


    namespace Planner
    {
        #define REGISTER_STATE(x, y) y,

        // Build an array of lambdas that are associative with the StateType enum
        const std::vector< std::function<bool(Entity*) > > kPredicates = {
            #include "RegisterStates.h"

            // This defines the end of the list
            [](Entity *entity)
            {
                return false;
            }
        };

        #undef REGISTER_STATE
    }
}
