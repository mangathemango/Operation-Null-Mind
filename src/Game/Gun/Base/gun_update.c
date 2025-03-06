#include <gun.h>
#include <player.h>
#include <input.h>
#include <math.h>

void Gun_Update() {
    GunData* gun = player.state.currentGun;


    gun->state.angle = atan2(
        Vec2_Subtract(Input->mouse.position, player.state.position).y, 
        Vec2_Subtract(Input->mouse.position, player.state.position).x
    ) * 180 / M_PI;

    gun->state.position = Vec2_Subtract(
                            player.state.position, 
                            (Vec2) {
                                gunAnimData.spriteSize.x / 2, 
                                gunAnimData.spriteSize.y / 2
                            }
                        );

    if (Input->mouse.position.x < player.state.position.x) {
        gun->state.rotationCenter = (SDL_Point) {gunAnimData.spriteSize.x / 2, gunAnimData.spriteSize.y / 2 - 6};
        gun->state.flip = SDL_FLIP_VERTICAL;
        gun->state.position.y += 12;
    } else {
        gun->state.rotationCenter = (SDL_Point) {gunAnimData.spriteSize.x / 2, gunAnimData.spriteSize.y / 2 + 6};
        gun->state.flip = SDL_FLIP_NONE;
    }

    gun->config.casingParticleEmitter->position = player.state.position;
    if (gun->state.flip == SDL_FLIP_NONE) {
        gun->config.casingParticleEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle - 135);
    } else {
        gun->config.casingParticleEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle + 135);
    }
    
    ParticleEmitter_Update(gun->config.casingParticleEmitter);

    Gun_AnimationUpdate();
}