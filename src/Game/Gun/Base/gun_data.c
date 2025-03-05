#include <gun.h>


Animation* gunAnimation = NULL;
AnimationData gunAnimData = {
    .spritesheetPath = "Assets/Images/guns.png",
    .frameSize = {50, 25},
    .frameCount = 5,
    .clips = {
        {
            .name = GUN_SHOTGUN,
            .startFrameIndex = 0,
            .endFrameIndex = 0,
            .frameDuration = 0.4f,
            .looping = false
        },
        {
            .name = GUN_BATTLE_RIFLE,
            .startFrameIndex = 1,
            .endFrameIndex = 1,
            .frameDuration = 0.4f,
            .looping = false
        },
        {
            .name = GUN_SMG,
            .startFrameIndex = 2,
            .endFrameIndex = 2,
            .frameDuration = 0.4f,
            .looping = false
        },
        {
            .name = GUN_ASSAULT_RIFLE,
            .startFrameIndex = 3,
            .endFrameIndex = 3,
            .frameDuration = 0.4f,
            .looping = false
        },
        {
            .name = GUN_PISTOL,
            .startFrameIndex = 4,
            .endFrameIndex = 4,
            .frameDuration = 0.4f,
            .looping = false
        },
    },
    .spriteSize = {50, 25},
    .defaultClip = GUN_PISTOL,
    .playOnStart = true,
};