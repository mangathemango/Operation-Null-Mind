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
                            (Vec2) {24, 12}
                        );
    gun->state.rotationCenter = (SDL_Point) {25, 13};
    
    if (Input->mouse.position.x < player.state.position.x) {
        gun->state.flip = SDL_FLIP_VERTICAL;
    } else {
        gun->state.flip = SDL_FLIP_NONE;
    }

    
    if (gun->state.flip == SDL_FLIP_NONE) {
        gun->config.casingParticleEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle - 135);
    } else {
        gun->config.casingParticleEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle + 135);
    }
    
    gun->config.casingParticleEmitter->position = player.state.position;
    ParticleEmitter_Update(gun->config.casingParticleEmitter);

    Gun_AnimationUpdate();
}