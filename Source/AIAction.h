/* ---------------------------------------------------------------------------
** Team Bear King
** © 2015 DigiPen Institute of Technology, All Rights Reserved.
**
** AIAction.h
**
** Author:
** - Jordan Ellis - j.ellis@digipen.edu
** - Joshua Shlemmer - joshua.shlemmer@digipen.edu
**
** -------------------------------------------------------------------------*/
#pragma once

#include "WorldState.h"

namespace Ursine
{
    typedef bool(*ActionHandler)(Entity *);

    class AIAction
    {
        // used for debugging
        std::string _name;

        uint _cost;

        // the flags in the world that are 
        // prerequisites for this action
        WorldState _pre_world;

        // the flags that this action changes
        // in the world
        WorldState _post_world;

        // the predicate that contains the action's logic
        ActionHandler _func;

    public:
        AIAction(void);
        AIAction(const std::string &name, ActionHandler func);

        AIAction &AddPre(StateType type, bool flag);
        AIAction &AddPost(StateType type, bool flag);

        WorldState GetPreWorld(void) const;
        WorldState GetPostWorld(void) const;

        uint GetCost(void) const;
        void SetCost(uint cost);

        std::string GetName(void) const;

        ActionHandler GetFunc(void) const;
    };
}
