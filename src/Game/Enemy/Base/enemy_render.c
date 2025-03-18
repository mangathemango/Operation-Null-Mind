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
        Animation_Render(
            enemies[i].resources.animation,
            Vec2_Subtract (
                Camera_WorldToScreen(enemies[i].state.position),
                Vec2_Multiply(enemies[i].animData.spriteSize, 0.5f)
            ),
            enemies[i].animData.spriteSize,
            0,
            NULL,
            SDL_FLIP_NONE
        );
    }
}