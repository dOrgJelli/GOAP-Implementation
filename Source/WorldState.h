/* ---------------------------------------------------------------------------
** Team Bear King
** © 2015 DigiPen Institute of Technology, All Rights Reserved.
**
** WorldState.h
**
** Author:
** - Jordan Ellis - j.ellis@digipen.edu
** - Joshua Shlemmer - joshua.shlemmer@digipen.edu
** 
** -------------------------------------------------------------------------*/
#pragma once

#include "StateArray.h"

namespace Ursine
{
    typedef uint64 WorldFlags;
    class AIAction;

    class WorldState
    {
        // Bit field of all the world's state flags
        WorldFlags _flags;
        WorldFlags _mask;

    public:
        WorldState(void);

        bool GetFlag(StateType type);
        WorldState &SetFlag(StateType type, bool flag);

        // Apply an AI action to the world state
        void ApplyAction(const AIAction &action);

        // Check for equivalent world states
        bool Compare(WorldState other) const;
        bool Compare(WorldState other, WorldFlags mask) const;

        // Get the bitfield of inactive flags
        WorldFlags GetMask(void) const;

        // Get the bitfield of active flags
        WorldFlags GetCare(void) const;

        // Get the bitfield of true flags
        WorldFlags GetFlags(void) const;

        friend 
        void UpdateCurrentWorld(WorldState &world, StateArray &states, uint itr_count);
    };
}
