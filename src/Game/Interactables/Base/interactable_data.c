#include <interactable.h>

Interactable interactableData[INTERACTABLE_COUNT] = {
    [INTERACTABLE_WEAPONCRATEOPEN] = {
        .type = INTERACTABLE_WEAPONCRATEOPEN,
        .hitboxSize = {40, 20},
        .interactionText = NULL,
        .spritePath = "Assets/Images/Interactables/weapon_crate_open.png",
        .renderSize = {40, 20}
    },
    [INTERACTABLE_WEAPONCRATECLOSED] = {
        .type = INTERACTABLE_WEAPONCRATECLOSED,
        .enabled = false,
        .hitboxSize = {40, 20},
        .interactionText = "Open Crate",
        .spritePath = "Assets/Images/Interactables/weapon_crate_closed.png",
        .renderSize = {40, 20}
    },
};