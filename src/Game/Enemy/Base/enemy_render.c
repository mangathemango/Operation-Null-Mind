#include <enemy.h>
#include <enemy_types.h>
#include <animation.h>
#include <camera.h>
#include <player.h>
#include <app.h>

/**
 * [Render] Renders all active enemies.
 * 
 * Iterates through the enemy array and calls each enemy's specific
 * render function if they are active.
 */
void Enemy_Render() {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].state.isDead) continue;
        if (!enemies[i].resources.animation) continue;
        if (enemies[i].state.isSpawning) {
            SDL_Rect dest = Tile_GetRectFromPixel(enemies[i].state.position);
            Vec2 position, size;
            Vec2_FromRect(dest, &position, &size);
            if (!Camera_RectIsOnScreen(dest)) continue;
            dest = Vec2_ToCenteredRect(Camera_WorldVecToScreen(position), size);
            SDL_RenderCopy(
                app.resources.renderer,
                Enemy_spawnIndicator,
                NULL,
                &dest
            );
            continue;
        }

        // don't render if the enemy is not in the view
        if (!Camera_RectIsOnScreen(enemies[i].state.collider.hitbox)) continue;
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
            enemies[i].state.direction.x < 0 ? 
            SDL_FLIP_HORIZONTAL :
            SDL_FLIP_NONE
        );
    }
}