/* ---------------------------------------------------------------------------
** Team Bear King
** © 2015 DigiPen Institute of Technology, All Rights Reserved.
**
** GOAPAstar.cpp
**
** Author:
** - Jordan Ellis - j.ellis@digipen.edu
** - Joshua Shlemmer - joshua.shlemmer@digipen.edu
**
** -------------------------------------------------------------------------*/
#include "Precompiled.h"

#include "GOAPAstar.h"

namespace Ursine
{
    // init static members
    std::vector<GOAPAstar::astarnode> GOAPAstar::_open;
    std::vector<GOAPAstar::astarnode> GOAPAstar::_closed;
    std::vector<std::pair<AIAction, WorldState>> GOAPAstar::_transitions;

    int GOAPAstar::calculateH(WorldState from, WorldState to)
    {
        auto care = to.GetCare();
        auto diff = ( ( from.GetFlags() & care ) ^ ( to.GetFlags() & care ) );
        
        int distance = 0;

        for (int i = 0; i < StateType::STATE_NUM; ++i)
            if ( ( diff & ( 1LL << i ) ) != 0 )
                ++distance;

        return distance;
    }

    int GOAPAstar::nodeInOpened(WorldState ws)
    {
        for (uint i = 0, n = _open.size(); i < n; ++i)
        {
            if (_open[i].ws.GetFlags() == ws.GetFlags())
                return i;
        }

        return -1;
    }

    int GOAPAstar::nodeInClosed(WorldState ws)
    {
        for (uint i = 0, n = _closed.size(); i < n; ++i)
        {
            if (_closed[i].ws.GetFlags() == ws.GetFlags())
                return i;
        }

        return -1;
    }

    void GOAPAstar::reconstructPlan(GOAPlanner *ap, astarnode *goal_node)
    {
        astarnode *curr = goal_node;
        auto &plan = ap->_plan;
        auto &actions = ap->_actions;

        // clear the plan
        plan.clear();

        while(curr && curr->action_name.length())
        {
            // find the action
            auto it = actions.find(curr->action_name);

            UAssert(it != actions.end(), "Action \"%s\" does not exist.", curr->action_name.c_str());

            // add the action handler to the plan
            plan.push_back(it->second.GetFunc());

            // check to see if parent is in the closed list
            int i = nodeInClosed(curr->parent_ws);
            curr = (i == -1) ? nullptr : &_closed[i];
        }
    }

    GOAPAstar::astarnode GOAPAstar::openPopLowest(void)
    {
        int index = -1;
        int lowest_val = std::numeric_limits<int>().max();

        for (int i = 0, n = _open.size(); i < n; ++i)
        {
            if (_open[i].f < lowest_val)
            {
                lowest_val = _open[i].f;
                index = i;
            }
        }

        astarnode node = _open[index];

        _open.erase(_open.begin() + index);

        return node;
    }

    void GOAPAstar::getPossibleStateTransitions(GOAPlanner *ap, WorldState state)
    {
        _transitions.clear();

        for (auto &pair : ap->_actions)
        {
            auto action = pair.second;

            auto pre = action.GetPreWorld();
            auto care = pre.GetCare();
            bool met = (pre.GetFlags() & care) == (state.GetFlags() & care);

            if (met)
            {
                // compute the future world
                WorldState to = state;
                to.ApplyAction(action);

                // add the action and the future world to the transitions array
                _transitions.emplace_back(std::make_pair(action, to));
            }
        }
    }

    /* from: http://theory.stanford.edu/~amitp/GameProgramming/ImplementationNotes.html
    OPEN = priority queue containing START
    CLOSED = empty set
    while lowest rank in OPEN is not the GOAL:
      current = remove lowest rank item from OPEN
      add current to CLOSED
      for neighbors of current:
        cost = g(current) + movementcost(current, neighbor)
        if neighbor in OPEN and cost less than g(neighbor):
          remove neighbor from OPEN, because new path is better
        if neighbor in CLOSED and cost less than g(neighbor): **
          remove neighbor from CLOSED
        if neighbor not in OPEN and neighbor not in CLOSED:
          set g(neighbor) to cost
          add neighbor to OPEN
          set priority queue rank to g(neighbor) + h(neighbor)
          set neighbor's parent to current
    */

    void GOAPAstar::Plan(GOAPlanner *ap)
    {
        // clear open and closed lists
        _open.clear();
        _closed.clear();

        // TODO: Early out if _current == _desired, add plan WANDER

        WorldState goal = ap->_desired;

        // put start in the open list
        astarnode start;

        start.ws = ap->_current;
        start.parent_ws = ap->_current;
        start.g = 0;
        start.h = calculateH(ap->_current, goal);
        start.f = start.g + start.h;
        start.action_name = "";

        _open.push_back(start);

        for (;;)
        {
            if (_open.size() == 0)
                return;

            // find the node with the lowest rank
            astarnode curr = openPopLowest();

            auto care = goal.GetCare();
            bool match = ((curr.ws.GetFlags() & care) == (goal.GetFlags() & care));

            // if we've reached our goal state
            if (match)
            {
                reconstructPlan(ap, &curr);

                // Success
                return;
            }

            // add current to closed
            _closed.push_back(curr);

            // fill the transitions array
            getPossibleStateTransitions(ap, curr.ws);

            // iterate over all possible transitions
            for (auto &pair : _transitions)
            {
                AIAction &action = pair.first;
                WorldState &future = pair.second;

                astarnode neighbor;

                int cost = curr.g + action.GetCost();
                int open_index = nodeInOpened(future);
                int close_index = nodeInClosed(future);

                // if neighbor is in OPEn and cost less than g(neighbor)
                if (open_index >= 0 && cost < _open[open_index].g)
                {
                    // remove neighbor from OPEN, because new patch is better
                    _open.erase(_open.begin() + open_index);

                    open_index = -1;
                }

                // if neighbor in CLOSED and cost less than g(neighbor)
                if (close_index >= 0 && cost < _closed[close_index].g)
                {
                    // remove neighbor from CLOSED
                    _closed.erase(_closed.begin() + close_index);
                }

                // if neighbor not in OPEN and neighbor not in CLOSED
                if (close_index == -1 && open_index == -1)
                {
                    neighbor.ws = future;
                    neighbor.g = cost;
                    neighbor.h = calculateH(neighbor.ws, goal);
                    neighbor.f = neighbor.g + neighbor.h;
                    neighbor.action_name = action.GetName();
                    neighbor.parent_ws = curr.ws;
                    
                    _open.push_back(neighbor);
                }
            }
        }

        return;
    }
}