#include <gun.h>
#include <math.h>
#include <input.h>
#include <player.h>

void Gun_Render() {
    float rotateAngle = atan2(
        Vec2_Subtract(Input->mouse.position, player.state.position).y, 
        Vec2_Subtract(Input->mouse.position, player.state.position).x
    ) * 180 / M_PI;
    SDL_Point rotationCenter;
    SDL_RendererFlip flip;
    Vec2 renderPosition =  Vec2_Subtract(
        player.state.position,
        Vec2_Divide(gunAnimData.spriteSize, 2)
    );
    if (Input->mouse.position.x < player.state.position.x) {
        rotationCenter = (SDL_Point) {
            gunAnimData.spriteSize.x / 2 , gunAnimData.spriteSize.y / 2 - 6
        };
        flip = SDL_FLIP_VERTICAL;
        renderPosition.y += 12;
    } else {
        rotationCenter = (SDL_Point) {
            gunAnimData.spriteSize.x / 2, gunAnimData.spriteSize.y / 2 + 6
        };
        flip = SDL_FLIP_NONE;
    }
    SDL_Log("%f", rotateAngle);
    Animation_Render(gunAnimation, 
                    renderPosition, 
                    gunAnimData.spriteSize,
                    rotateAngle,
                    &rotationCenter,
                    flip);

    ParticleEmitter_Render(player.state.currentGun->config.casingParticleEmitter);
}