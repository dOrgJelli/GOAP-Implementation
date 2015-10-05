/* ---------------------------------------------------------------------------
** Team Bear King
** © 2015 DigiPen Institute of Technology, All Rights Reserved.
**
** ActionHandlers.cpp
**
** Author:
** - Jordan Ellis - j.ellis@digipen.edu
** - Joshua Shlemmer - joshua.shlemmer@digipen.edu
**
** -------------------------------------------------------------------------*/
#include "Precompiled.h"

#include "ActionHandlers.h"

// Here are some examples of Action Handlers:

bool ShootActionHandler(Entity *entity)
{
    auto virtual_gamepad = entity->GetComponent<AIController>()->GetVirtualGamepad();
    auto target = entity->GetComponent<AITargetFinder>()->GetTarget();

    // shoot at the target
    virtual_gamepad.SetTriggerRight(1.0f);

    if (target)
    {
        auto health = target->GetComponent<HealthComponent>();

        if (health && health->GetHealth() <= 0.0f)
            virtual_gamepad.SetTriggerRight(0.0f);
    }

    return true;
}

bool ShieldActionHandler(Entity *entity)
{
    // press the button on the gamepad for the shield
    auto virtual_gamepad = entity->GetComponent<AIController>()->GetVirtualGamepad();

    virtual_gamepad.Press(BTN_B);

    entity->GetTimers().Create(TimeSpan::FromSeconds(0.1f))
        .Completed([=]
    { 
        virtual_gamepad.Release(BTN_B); 
    });

    return true;
}

bool ChaseActionHandler(Entity *entity)
{
    auto target_finder = entity->GetComponent<AITargetFinder>();

    if (target_finder)
    {
        auto target = target_finder->GetTarget();

        if (target)
        {
            auto target_pos = Vector2(target->GetTransform()->PositionWC());

            // add a random vector so we aren't always directly on top of him
            target_pos += Vector2::AngleVec(Math::Rand(0.0f, Math::PI_2)) * 10.0f;

            // set the AI controller's target position
            entity->GetComponent<AIController>()->SetTarget(target_pos);
        }
    }

    return true;
}

bool ScatterActionHandler(Entity *entity)
{
    // press the button on the gamepad for the scatter shot
    auto virtual_gamepad = entity->GetComponent<AIController>()->GetVirtualGamepad();

    virtual_gamepad.Press(BTN_SHOULDER_RIGHT);

    entity->GetTimers().Create(TimeSpan::FromSeconds(Math::Rand(0.1f, 1.2f)))
        .Completed([=]{ virtual_gamepad.Release(BTN_SHOULDER_RIGHT); });

    return true;
}

bool PlaceBombsActionHandler(Entity *entity)
{
    // chase the target
    ChaseActionHandler(entity);

    // once we are close to it, place bombs
    if (Planner::kPredicates[STATE_TARGET_MID_RANGE](entity))
    {
        auto virtual_gamepad = entity->GetComponent<AIController>()->GetVirtualGamepad();

        auto player = entity->GetComponent<PlayerComponent>();

        if (player)
        {
            auto bombs = player->GetAbilities().Get<Bomb>();

            if (bombs)
            {
                if (bombs->NoAmmo())
                {
                    virtual_gamepad.Press(BTN_Y);

                    entity->GetTimers().Create(TimeSpan::FromSeconds(0.1f))
                        .Completed([=]{ virtual_gamepad.Release(BTN_Y); });

                    return true;
                }
                else
                    return false;
            }
        }
    }

    return false;
}
