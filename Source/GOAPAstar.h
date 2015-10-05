/* ---------------------------------------------------------------------------
** Team Bear King
** © 2015 DigiPen Institute of Technology, All Rights Reserved.
**
** GOAPAstar.h
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
    class GOAPAstar
    {
        struct astarnode
        {
            int g; // Distance to goal
            int h; // Heuristic
            int f; // Total cost
            
            WorldState ws;
            WorldState parent_ws;

            // Used for debugging
            std::string action_name;
        };

        // Calculate the heuristic
        static int calculateH(WorldState from, WorldState to);

        // Check to see if this world state is contained in a node 
        // in the open and closed list.  Returns the index of that node.
        static int nodeInOpened(WorldState ws);
        static int nodeInClosed(WorldState ws);

        // Reconstructs the plan from a given point back to the start node
        static void reconstructPlan(GOAPlanner *ap, astarnode *goal_node);

        // Get the lowest cost node in the open list
        static astarnode openPopLowest(void);

        // Get all possible transitions from the current world state
        static void getPossibleStateTransitions(GOAPlanner *ap, WorldState state);

        static std::vector<astarnode> _open;
        static std::vector<astarnode> _closed;
        static std::vector<std::pair<AIAction, WorldState>> _transitions;

    public:
        static void Plan(GOAPlanner *ap);
    };
}
