/* ---------------------------------------------------------------------------
** Team Bear King
** © 2015 DigiPen Institute of Technology, All Rights Reserved.
**
** GOAPlanner.cpp
**
** Author:
** - Jordan Ellis - j.ellis@digipen.edu
** - Joshua Shlemmer - joshua.shlemmer@digipen.edu
**
** -------------------------------------------------------------------------*/
#include "Precompiled.h"

#include "GOAPlanner.h"
#include "GOAPAstar.h"

namespace Ursine
{
    GOAPlanner::GOAPlanner(void)
        : BaseComponent()
        , _itr_count(0)
        , _interval(TimeSpan::FromSeconds(1.0f))
    {

    }

    void GOAPlanner::OnInitialize(void)
    {
        _states.SetOwner(GetOwner());

        updateCurrent();
    }

    AIAction &GOAPlanner::AddAction(const std::string &name, ActionHandler func)
    {
        auto itr = _actions.find(name);

        UAssert(itr == _actions.end(), "The action \"%s\" has already been added.", name.c_str());

        // add the action to the actions map
        _actions.emplace(std::make_pair(name, AIAction(name, func)));

        return _actions[name];
    }

    TimeSpan GOAPlanner::GetUpdateInterval(void) const
    {
        return _interval;
    }

    void GOAPlanner::SetUpdateInterval(TimeSpan interval)
    {
        _interval = interval;
    }

    void GOAPlanner::updateCurrent(void)
    {
        GetOwner()->GetTimers().Create(_interval, kTimerGroupGameplay)
            .Completed([=]{
            
            // update the current world
            UpdateCurrentWorld(_current, _states, ++_itr_count);

            // Create a new plan for ourselves
            GOAPAstar::Plan(this);

            // recursively call this function
            updateCurrent();

        });
    }

    void GOAPlanner::SetDesiredWorldState(WorldState desired)
    {
        _desired = desired;
    }
}
