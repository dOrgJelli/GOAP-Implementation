/* ---------------------------------------------------------------------------
** Team Bear King
** © 2015 DigiPen Institute of Technology, All Rights Reserved.
**
** GOAPlanner.h
**
** Author:
** - Jordan Ellis - j.ellis@digipen.edu
** - Joshua Shlemmer - joshua.shlemmer@digipen.edu
**
** -------------------------------------------------------------------------*/
#pragma once

#include "WorldState.h"
#include "AIAction.h"

namespace Ursine
{
    class GOAPlanner : public Component
    {
        friend class GOAPAstar;
        friend class GOAPlannerSystem;

        WorldState _current;
        WorldState _desired;

        StateArray _states;

        // Keeps track of the last iteration this was updated
        uint _itr_count;

        // the interval at which we're updating at
        TimeSpan _interval;

        // map of all possible actions
        std::unordered_map<std::string, AIAction> _actions;

        // the plan we're executing
        std::vector<ActionHandler> _plan;

        // helper for updating the current world state
        void updateCurrent(void);

    public:
        GOAPlanner(void);

        void OnInitialize(void) override;

        // add a possible action for this planner
        AIAction &AddAction(const std::string &name, ActionHandler func);

        // get and set the interval at which we're updating our current world
        TimeSpan GetUpdateInterval(void) const;
        void SetUpdateInterval(TimeSpan interval);

        void SetDesiredWorldState(WorldState desired);
    };
}

#ifndef GOAPLANNER_REGISTERED
#define GOAPLANNER_REGISTERED

RegisterComponent(GOAPlanner);

#endif
