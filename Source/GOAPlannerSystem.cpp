/* ---------------------------------------------------------------------------
** Team Bear King
** © 2015 DigiPen Institute of Technology, All Rights Reserved.
**
** GOAPlannerSystem.cpp
**
** Author:
** - Jordan Ellis - j.ellis@digipen.edu
** - Joshua Shlemmer - joshua.shlemmer@digipen.edu
**
** -------------------------------------------------------------------------*/
#include "Precompiled.h"

#include "GOAPlannerSystem.h"

namespace Ursine
{
    GOAPlannerSystem::GOAPlannerSystem(World *world)
        : FilterSystem(world, Filter().All<GOAPlanner>())
    {

    }

    void GOAPlannerSystem::Process(Entity *entity)
    {
        // get the planner
        auto planner = entity->GetComponent<GOAPlanner>();
        auto &plan = planner->_plan;

        if (plan.size())
        {
            // go through the planner's plan
            bool result = plan.back()(entity);

            if (result)
                plan.pop_back();
        }
    }
}
