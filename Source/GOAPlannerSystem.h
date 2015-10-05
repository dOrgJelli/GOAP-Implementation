/* ---------------------------------------------------------------------------
** Team Bear King
** © 2015 DigiPen Institute of Technology, All Rights Reserved.
**
** GOAPlannerSystem.h
**
** Author:
** - Jordan Ellis - j.ellis@digipen.edu
** - Joshua Shlemmer - joshua.shlemmer@digipen.edu
**
** -------------------------------------------------------------------------*/
#pragma once

#include <FilterSystem.h>

namespace Ursine
{
    // This is the "filter system" that is responsible for
    // procesing all entities with the "Planner" component.
    // To learn more about how Entity-Component-System engine's
    // work, see: 
    // https://github.com/junkdog/artemis-odb/wiki/Introduction-to-Entity-Systems
    class GOAPlannerSystem : public FilterSystem
    {
    public:
        GOAPlannerSystem(World *world);

        void Process(Entity *entity) override;
    };
}

#ifndef GOAPLANNER_SYSTEM_REGISTERED
#define GOAPLANNER_SYSTEM_REGISTERED

RegisterEntitySystem(GOAPlannerSystem);

#endif