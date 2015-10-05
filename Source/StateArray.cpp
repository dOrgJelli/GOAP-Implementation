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
#include "Precompiled.h"

#include "StateArray.h"

namespace Ursine
{
    StateArray::StateArray(void)
        : _owner(nullptr)
    {
        // initialize states
        for (uint i = 0; i < StateType::STATE_NUM; ++i)
        {
            auto &state = _states[i];
            state.itr_count = 0;
        }
    }

    void StateArray::SetOwner(Entity *owner)
    {
        _owner = owner;
    }

    bool StateArray::GetState(StateType type, uint itr_count)
    {
        // if the state is out of date
        if (_states[type].itr_count < itr_count)
        {
            // update the iteration count
            _states[type].itr_count = itr_count;

            // update the flag
            _states[type].flag = Planner::kPredicates[type](_owner);
        }

        return _states[type].flag;
    }
}
