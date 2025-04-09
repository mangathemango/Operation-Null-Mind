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