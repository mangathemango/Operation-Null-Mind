/**
 * @file enemy_render.c
 * @brief Renders all enemy types
 *
 * Coordinates the rendering of all active enemies,
 * including spawn indicators and special effects.
 *
 * @author Mango
 * @date 2025-03-04
 */

#include <enemy.h>
#include <enemy_types.h>
#include <animation.h>
#include <camera.h>
#include <player.h>
#include <app.h>

/**
 * @brief [Render] Renders all active enemies
 * 
 * Iterates through the enemy array and calls each enemy's specific
 * render function if they are active.
 */
void Enemy_Render() {
    ParticleEmitter_Render(TacticianBuffEffectEmitter);
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].state.isDead) continue;
        if (!enemies[i].resources.animation) continue;
        if (enemies[i].state.isSpawning) {
            SDL_Rect dest = Tile_GetRectFromPixel(enemies[i].state.position);
            Vec2 position, size;
            Vec2_FromRect(dest, &position, &size);
            
            float timeLeft = Timer_GetTimeLeft(enemies[i].resources.timer);
            int opacity = 255;
            if (timeLeft > 0.5f) {
                /*
                    The size of the indicator grows as the enemy is about to spawn
                    size function can be written as: 
                    s(t) = 1 + (maxSize * (t - timeLeft)) ^ (easeRate)
                */ 
                float maxSize = 3.0f;
                float easeRate = 4.0f;
                float multipler = 1 + SDL_pow (maxSize * (timeLeft - 0.5f), easeRate);

                size = Vec2_Multiply(size, multipler);
                opacity = 255 - (200 * (timeLeft - 0.5f) / 0.5f);
            }

            if (!Camera_WorldRectIsOnScreen(dest)) continue;
            dest = Vec2_ToCenteredRect(Camera_WorldVecToScreen(position), size);

            SDL_SetTextureAlphaMod(Enemy_spawnIndicator, opacity);
            SDL_RenderCopy(
                app.resources.renderer,
                Enemy_spawnIndicator,
                NULL,
                &dest
            );
            continue;
        }

        if (enemies[i].type == ENEMY_TYPE_LIBET) {
            continue;
        }
        // don't render if the enemy is not in the view
        if (Camera_WorldRectIsOnScreen(enemies[i].state.collider.hitbox))
        
        Animation_Render(
            enemies[i].resources.animation,
            Camera_WorldVecToScreen(
                Vec2_ToCenteredPosition(
                    enemies[i].state.position, 
                    enemies[i].animData.spriteSize
                )
            ),
            enemies[i].animData.spriteSize,
            0,
            NULL,
            enemies[i].state.flip
        );
        if (enemies[i].render) enemies[i].render(&enemies[i]);
    }
    Enemy_RenderHealthTexts();
    if (KamikazeExplosionEmitter) ParticleEmitter_Render(KamikazeExplosionEmitter);
    Proxy_RenderParticles();
    Sabot_RenderParticles();
    Vantage_RenderParticles();
    Tactician_RenderParticles();
    Sentry_RenderParticles();
    Radius_RenderParticles();
    Juggernaut_RenderParticles();
    Echo_RenderParticles();  // Add Echo particles render
}