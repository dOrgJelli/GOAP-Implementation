/* ---------------------------------------------------------------------------
** Team Bear King
** © 2015 DigiPen Institute of Technology, All Rights Reserved.
**
** WorldState.cpp
**
** Author:
** - Jordan Ellis - j.ellis@digipen.edu
** - Joshua Shlemmer - joshua.shlemmer@digipen.edu
** 
** -------------------------------------------------------------------------*/
#include "Precompiled.h"

#include "WorldState.h"
#include "Utils.h"

namespace Ursine
{
    WorldState::WorldState(void)
        : _flags(0)
        , _mask(-1LL)
    {

    }

    bool WorldState::GetFlag(StateType type)
    {
        return Utils::IsFlagSet(_flags, WorldFlags(1 << type));
    }

    WorldState &WorldState::SetFlag(StateType type, bool flag)
    {
        if (flag)
        {
            Utils::FlagSet(_flags, WorldFlags(1 << type));
        }
        else
        {
            Utils::FlagUnset(_flags, WorldFlags(1 << type));
        }

        Utils::FlagUnset(_mask, WorldFlags(1 << type));

        return *this;
    }

    void WorldState::ApplyAction(const AIAction &action)
    {
        auto post_world = action.GetPostWorld();

        auto unaffected = post_world._mask;
        auto affected = (unaffected ^ -1LL);

        _flags = (_flags & unaffected) | (post_world._flags & affected);
        _mask &= post_world._mask;
    }

    bool WorldState::Compare(WorldState other) const
    {
        return Compare(other, _mask);
    }

    bool WorldState::Compare(WorldState other, WorldFlags mask) const
    {
        // Make sure we are only comparing the flags we want checked
        auto this_field = _flags ^ mask;
        auto other_field = other._flags ^ mask;

        return this_field == other_field;
    }

    WorldFlags WorldState::GetMask(void) const
    {
        return _mask;
    }

    WorldFlags WorldState::GetFlags(void) const
    {
        return _flags;
    }

    WorldFlags WorldState::GetCare(void) const
    {
        return _mask ^ -1LL;
    }

    void UpdateCurrentWorld(WorldState &world, StateArray &states, uint itr_count)
    {
        world._flags = 0;
        world._mask = -1LL;

        for (uint i = 0; i < StateType::STATE_NUM; ++i)
        {
            auto type = StateType(i);
            bool flag = states.GetState(type, itr_count);

            world.SetFlag(type, flag);
        }
    }
}
