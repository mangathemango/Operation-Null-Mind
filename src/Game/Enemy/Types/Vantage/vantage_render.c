/**
 * @file vantage_render.c
 * @brief Renders Vantage enemy type
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_vantage.h>
#include <camera.h>
#include <app.h>
#include <circle.h>

void Vantage_Render(EnemyData* data) {
    VantageConfig *config = (VantageConfig*)data->config;
    if (!config) return;
    GunData *gun = &config->gun;
    Vantage_UpdateGun(data);
    Animation_Render(
        gun->resources.animation, 
        Camera_WorldVecToScreen(gun->state.position), 
        gun->animData.spriteSize,
        gun->state.angle,
        &gun->state.rotationCenter,
        gun->state.flip
    );

    Vec2 currentLazerPosition = gun->resources.muzzleFlashEmitter->position;
    Vec2 targetDirection = Vec2_Normalize(
        Vec2_Subtract(
            player.state.position, 
            gun->resources.muzzleFlashEmitter->position
        )
    );
    Collider lazer = (Collider) {
        .active = true,
        .hitbox = Vec2_ToSquareRect(
            currentLazerPosition, 
            1
        ),
        .collidesWith = COLLISION_LAYER_ENVIRONMENT
    };
    Collider_Register(&lazer, NULL);
    for (int i = 0; !Collider_Check(&lazer, NULL) && i < 1000; i++) {
        if (Vec2_AreEqual(targetDirection, Vec2_Zero)) {
            break;
        }
        Vec2_Increment(&currentLazerPosition, targetDirection);
        lazer.hitbox = Vec2_ToSquareRect(currentLazerPosition, 1);
    }
    Vec2 hitPoint = Camera_WorldVecToScreen(currentLazerPosition);
    Vec2 lazerStartPoint = Camera_WorldVecToScreen(gun->resources.muzzleFlashEmitter->position);
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(
        app.resources.renderer, 
        lazerStartPoint.x, lazerStartPoint.y, 
        hitPoint.x, hitPoint.y
    );
    Collider_Reset(&lazer);
}

void Vantage_RenderParticles() {
    if (!VantageBulletEmitter) return;
    ParticleEmitter_Render(VantageBulletEmitter);
    ParticleEmitter_Render(VantageMuzzleFlashEmitter);
    ParticleEmitter_Render(VantageCasingEmitter);
    ParticleEmitter_Render(VantageBulletFragmentsEmitter);
}
