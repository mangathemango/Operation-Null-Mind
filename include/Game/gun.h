#pragma once

#include <animation.h>
#include <vec2.h>
#include <particle_emitterpresets.h>

#define GUN_SHOTGUN "Beretta 1301 Tactical"
#define GUN_BATTLE_RIFLE "FN SCAR-H"
#define GUN_SMG "KRISS Vector"
#define GUN_ASSAULT_RIFLE "M4A1 URG-I"
#define GUN_PISTOL "Glock 17"

typedef struct {
    ParticleEmitter* casingParticleEmitter;
    ParticleEmitter* muzzleFlashEmitter;
} GunConfig;

typedef struct {
    Vec2 position;
    float angle;
    SDL_RendererFlip flip;
    SDL_Point rotationCenter;
} GunState;

typedef struct {
    char* name;
} GunStats;

typedef struct {
    GunConfig config;
    GunState state;
    GunStats stats;
} GunData;

extern GunData Gun_Pistol;
extern GunData Gun_SMG;
extern GunData Gun_Shotgun;
extern GunData Gun_AssaultRifle;
extern GunData Gun_BattleRifle;
extern AnimationData gunAnimData;

extern Animation* gunAnimation;
void Gun_AnimationInit();
void Gun_AnimationUpdate();
void Gun_Render();
void Gun_Start();
void Gun_Update();