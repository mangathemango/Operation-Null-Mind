#include <interactable.h>
#include <player.h>

#define ENTIRE_SRC_RECT {-1, -1, -1, -1}

Interactable interactableData[INTERACTABLE_COUNT] = {
    [INTERACTABLE_WEAPONCRATEOPEN] = {
        .type = INTERACTABLE_WEAPONCRATEOPEN,
        .enabled = false,
        .hitboxSize = {40, 20},
        .interactionText = NULL,
        .spritePath = "Assets/Images/Interactables/weapon_crate_open.png",
        .srcRect = ENTIRE_SRC_RECT,
        .callback = NULL,
        .renderSize = {40, 20}
    },
    [INTERACTABLE_WEAPONCRATECLOSED] = {
        .type = INTERACTABLE_WEAPONCRATECLOSED,
        .enabled = true,
        .hitboxSize = {40, 20},
        .interactionText = "Open Crate",
        .spritePath = "Assets/Images/Interactables/weapon_crate_closed.png",
        .srcRect = ENTIRE_SRC_RECT,
        .callback = Player_OpenCrate,
        .renderSize = {40, 20}
    },
    [INTERACTABLE_LOG] = {
        .type = INTERACTABLE_LOG,
        .enabled = true,
        .hitboxSize = {20, 20},
        .interactionText = "Read Log",
        .spritePath = "Assets/Images/Interactables/log.png",
        .srcRect = ENTIRE_SRC_RECT,
        .callback = Player_ReadLog,
        .renderSize = {20, 20}
    },
    [INTERACTABLE_WEAPON] = {
        .type = INTERACTABLE_WEAPON,
        .enabled = true,
        .hitboxSize = {20, 20},
        .interactionText = NULL,
        .spritePath = NULL,
        .srcRect = ENTIRE_SRC_RECT,
        .callback = Player_PickUpGun,
        .renderSize = {10, 10}
    },

    [INTERACTABLE_EXIT] = {
        .type = INTERACTABLE_EXIT,
        .enabled = true,
        .hitboxSize = {120, 80},
        .interactionText = "Next Stage",
        .spritePath = "Assets/Images/Interactables/exit_door.png",
        .srcRect = ENTIRE_SRC_RECT,
        .callback = Game_TransitionNextLevel,
        .renderSize = {120, 80}
    },
    [INTERACTABLE_HEALTH] = 
    {
        .type = INTERACTABLE_HEALTH,
        .enabled = true,
        .hitboxSize = {20, 20},
        .spritePath = "Assets/Images/Icons/health/small.png",
        .srcRect = ENTIRE_SRC_RECT,
        .callback = Player_PickUpHealth,
        .renderSize = {30 , 30}
    },
    [INTERACTABLE_HEALTH_MEDIUM] = 
    {
        .type = INTERACTABLE_HEALTH,
        .enabled = true,
        .hitboxSize = {20, 20},
        .spritePath = "Assets/Images/Icons/health/medium.png",
        .srcRect = ENTIRE_SRC_RECT,
        .callback = Player_PickUpHealth,
        .renderSize = {30 , 30}
    },
    [INTERACTABLE_HEALTH_LARGE] = 
    {
        .type = INTERACTABLE_HEALTH,
        .enabled = true,
        .hitboxSize = {20, 20},
        .spritePath = "Assets/Images/Icons/health/big.png",
        .srcRect = ENTIRE_SRC_RECT,
        .callback = Player_PickUpHealth,
        .renderSize = {30 , 30}
    },
    [INTERACTABLE_ABILITIES] = 
    {
        .type = INTERACTABLE_ABILITIES,
        .enabled = true,
        .hitboxSize = {20, 20},
        .spritePath = "Assets/Images/Interactables/abilities.png",
        .srcRect = ENTIRE_SRC_RECT,
        .callback = Player_PickUpSkill,
        .renderSize = {20 , 20}
    }
};

HealthData healthData[3] = {
    [0] = {50, "Medi-Stim (+50 HP)"},
    [1] = {100, "Biofoam Spray (+100 HP)"},
    [2] = {200, "Nano-Gel (+200 HP)"}
};

AbilityData abilityData[8] =
{
    [ARMORED_UP] = 
    {
        .type = ARMORED_UP,
        .name = "Shielded Up",
        .descriptionPro = "Take less damage from enemies",
        .descriptionCon = "Do less damage to enemies",
        .path = "Assets/Images/Icons/abilities/shieldUp.png",
    },
    [GHOST_LOAD] =
    {
        .type = GHOST_LOAD,
        .name = "Ghost Load",
        .descriptionPro = "Every 8th shot doesn't use ammo",
        .descriptionCon = "Chance to jam your gun",
        .path = "Assets/Images/Icons/abilities/ghostLoad.png",
    },
    [HEMO_CYCLE] =
    {
        .type = HEMO_CYCLE,
        .name = "Hemocycle",
        .descriptionPro = "Every 10th kill heals you",
        .descriptionCon = "Takes more damage from enemies",
        .path = "Assets/Images/Icons/abilities/hemocycle.png",
    },
    [KINETIC_ARMOR] =
    {
        .type = KINETIC_ARMOR,
        .name = "Kinetic Armor",
        .descriptionPro = "Chance to not take damage",
        .descriptionCon = "Loses 20 ammo everytime it activates",
        .path = "Assets/Images/Icons/abilities/kineticArmor.png",
    },
    [LAST_STAND] =
    {
        .type = LAST_STAND,
        .name = "Last Stand",
        .descriptionPro = "Gives a second life",
        .descriptionCon = "All abilites have a longer cooldown",
        .path = "Assets/Images/Icons/abilities/lastStand.png",
    },
    [OVER_PRESSURED] =
    {
        .type = OVER_PRESSURED,
        .name = "Overpressured",
        .descriptionPro = "Increase fire rate and projectile speed",
        .descriptionCon = "Every shot drains extra ammo",
        .path = "Assets/Images/Icons/abilities/overPressured.png",
    },
    [SCAVENGER] =
    {
        .type = SCAVENGER,
        .name = "Scavenger",
        .descriptionPro = "Ammo drops increased",
        .descriptionCon = "Reduce max ammo capacity",
        .path = "Assets/Images/Icons/abilities/scavenger.png",
    }
};