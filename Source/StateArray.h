/* ---------------------------------------------------------------------------
** Team Bear King
** © 2015 DigiPen Institute of Technology, All Rights Reserved.
**
** StateArray.h
**
** Author:
** - Jordan Ellis - j.ellis@digipen.edu
** - Joshua Shlemmer - joshua.shlemmer@digipen.edu
**
** -------------------------------------------------------------------------*/
#pragma once

#include "StateArrayConfig.h"

namespace Ursine
{
    class StateArray
    {
        struct State
        {
            // used for invalidating the flag
            uint itr_count;
            bool flag;
        };

        // associative array of states
        State _states[StateType::STATE_NUM];
        
        Entity *_owner;

    public:
        StateArray(void);

        void SetOwner(Entity *owner);

        // Get the current state for this entities iteration
        bool GetState(StateType type, uint itr_count);
    };
}

