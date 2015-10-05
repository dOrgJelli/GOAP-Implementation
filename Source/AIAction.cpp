/* ---------------------------------------------------------------------------
** Team Bear King
** © 2015 DigiPen Institute of Technology, All Rights Reserved.
**
** AIAction.cpp
**
** Author:
** - Jordan Ellis - j.ellis@digipen.edu
** - Joshua Shlemmer - joshua.shlemmer@digipen.edu
**
** -------------------------------------------------------------------------*/
#include "Precompiled.h"

#include "AIAction.h"

namespace Ursine
{
    AIAction::AIAction(void)
        : _name("UNDEFINED")
        , _cost(0)
        , _func(nullptr)
    {

    }

    AIAction::AIAction(const std::string &name, ActionHandler func)
        : _name(name)
        , _cost(0)
        , _func(func)
    {
        
    }

    AIAction &AIAction::AddPre(StateType type, bool flag)
    {
        _pre_world.SetFlag(type, flag);

        return *this;
    }

    AIAction &AIAction::AddPost(StateType type, bool flag)
    {
        _post_world.SetFlag(type, flag);

        return *this;
    }

    WorldState AIAction::GetPreWorld(void) const
    {
        return _pre_world;
    }

    WorldState AIAction::GetPostWorld(void) const
    {
        return _post_world;
    }

    uint AIAction::GetCost(void) const
    {
        return _cost;
    }

    void AIAction::SetCost(uint cost)
    {
        _cost = cost;
    }

    ActionHandler AIAction::GetFunc(void) const
    {
        return _func;
    }

    std::string AIAction::GetName(void) const
    {
        return _name;
    }
}
