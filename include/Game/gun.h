/*
    @file gun.h
*   This file contains the gun data and its functions.
?   This includes the gun's animations, rendering, and updating.

?   Written by Mango on 06/03/2025
*/

#pragma once

#include <animation.h>
#include <vec2.h>
#include <particle_emitterpresets.h>

#define GUN_COUNT 5

// The gun names (I'm not a gun guy so this will be easier to work with)
#define GUN_SHOTGUN "Beretta 1301 Tactical"
#define GUN_BATTLE_RIFLE "FN SCAR-H"
#define GUN_SMG "KRISS Vector"
#define GUN_ASSAULT_RIFLE "M4A1 URG-I"
#define GUN_PISTOL "Glock 17"

typedef struct {
    ParticleEmitter* casingParticleEmitter;
    ParticleEmitter* muzzleFlashEmitter;
    Animation* animation;
} GunResources;

typedef struct {
    Vec2 position;
    float angle;
    SDL_RendererFlip flip;
    SDL_Point rotationCenter;
} GunState;

typedef struct {
    Vec2 muzzlePosition;
    Vec2 ejectionPosition;
    Vec2 gripPosition;
} GunConfig;

typedef struct {

} GunStats;

typedef struct {
    char* name;
    GunResources resources;
    GunState state;
    GunConfig config;
    GunStats stats;
    AnimationData animData;
} GunData;

extern GunData Gun_Pistol;
extern GunData Gun_SMG;
extern GunData Gun_Shotgun;
extern GunData Gun_AssaultRifle;
extern GunData Gun_BattleRifle;

extern GunData GunList[GUN_COUNT];

void Gun_AnimationInit();
void Gun_AnimationUpdate();
void Gun_Render();
void Gun_Start();
void Gun_Update();