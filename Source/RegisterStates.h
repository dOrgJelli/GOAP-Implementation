/* ---------------------------------------------------------------------------
** Team Bear King
** © 2015 DigiPen Institute of Technology, All Rights Reserved.
**
** RegisterStates.h
**
** Author:
** - Jordan Ellis - j.ellis@digipen.edu
** - Joshua Shlemmer - joshua.shlemmer@digipen.edu
**
** -------------------------------------------------------------------------*/

// NOTE: Do not include any files in this header.  Please see
// StateArrayConfig.h for more info.

// Here are some examples of state definitions.

REGISTER_STATE(TARGET_DEAD, [](Entity *entity)
{
    auto target_finder = entity->GetComponent<AITargetFinder>();

    if (target_finder)
    {
        auto target = target_finder->GetTarget();

        if (target)
            return false;
    }

    return true;
})

REGISTER_STATE(LOW_HEALTH, [](Entity *entity)
{
    auto health = entity->GetComponent<HealthComponent>();

    if (health)
    {
        if (health->GetHealth() / health->GetMaxHealth() <= 0.5f)
            return true;
    }

    return false;
})

REGISTER_STATE(SCATTER_READY, [](Entity *entity)
{
    auto player = entity->GetComponent<PlayerComponent>();

    if (player)
    {
        auto scatter = player->GetAbilities().Get<Scattershot>();

        if (scatter)
            return !scatter->OnCooldown();
    }

    return false;
})

REGISTER_STATE(BOMBS_FULL, [](Entity *entity)
{
    auto player = entity->GetComponent<PlayerComponent>();

    if (player)
    {
        auto bombs = player->GetAbilities().Get<Bomb>();

        if (bombs)
        {
            return bombs->FullAmmo();
        }
    }

    return false;
})
