#include <enemy.h>
#include <enemy_types.h>
#include <animation.h>
#include <camera.h>
#include <player.h>
#include <app.h>

void Enemy_Render() {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].state.isDead) continue;
        if (!enemies[i].resources.animation) continue;
        if (enemies[i].state.isSpawning) {
            SDL_Rect dest = Tile_GetRectFromPixel(enemies[i].state.position);
            Vec2 position, size;
            Vec2_FromRect(dest, &position, &size);
            if (!Camera_RectIsOnScreen(dest)) continue;
            dest = (SDL_Rect) {
                Camera_WorldVecToScreen(position).x,
                Camera_WorldVecToScreen(position).y,
                size.x,
                size.y
            };
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