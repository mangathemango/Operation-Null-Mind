#include <interactable.h>

Interactable interactableData[INTERACTABLE_COUNT] = {
    [INTERACTABLE_WEAPONCRATEOPEN] = {
        .type = INTERACTABLE_WEAPONCRATEOPEN,
        .hitboxSize = {40, 20},
        .interactionText = NULL,
        .spritePath = "Assets/Images/Interactables/weapon_crate_open.png",
        .srcRect = {-1, -1, -1, -1},
        .callback = NULL,
        .renderSize = {40, 20}
    },
    [INTERACTABLE_WEAPONCRATECLOSED] = {
        .type = INTERACTABLE_WEAPONCRATECLOSED,
        .enabled = true,
        .hitboxSize = {40, 20},
        .interactionText = "Open Crate",
        .spritePath = "Assets/Images/Interactables/weapon_crate_closed.png",
        .srcRect = {-1, -1, -1, -1},
        .callback = NULL,
        .renderSize = {40, 20}
    },
    [INTERACTABLE_WEAPON] = {
        .type = INTERACTABLE_WEAPON,
        .enabled = true,
        .hitboxSize = {20, 20},
        .interactionText = NULL,
        .spritePath = "Assets/Images/Interactables/weapon_crate_closed.png",
        .srcRect = {-1, -1, -1, -1},
        .callback = NULL,
        .renderSize = {10, 10}
    },
};