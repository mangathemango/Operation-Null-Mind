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