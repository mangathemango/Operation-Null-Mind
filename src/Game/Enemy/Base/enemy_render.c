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
            enemies[i].resources.animation,
            Camera_WorldToScreen(enemies[i].state.position),
            enemies[i].animData.spriteSize,
            0,
            NULL,
            SDL_FLIP_NONE
        );
    }
}