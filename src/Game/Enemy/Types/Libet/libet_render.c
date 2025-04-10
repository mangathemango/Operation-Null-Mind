#include <enemy_libet.h>
#include <camera.h>
#include <particle_emitterpresets.h>
#include <UI_text.h>
#include <app.h>

void Enemy_RenderBoss() {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].state.isDead) continue;
        if (enemies[i].state.isSpawning) continue;
        if (enemies[i].type == ENEMY_TYPE_LIBET) {
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
            Libet_Render(&enemies[i]);
        }
    }
}

/**
 * @brief [Render] Renders the Libet boss enemy
 *
 * This function handles the rendering of the Libet boss enemy.
 *
 * @param data Pointer to the enemy data structure
 */
void Libet_Render(EnemyData* data) {
    // Render bullet emitter
    if (LibetBulletEmitter) {
        ParticleEmitter_Render(LibetBulletEmitter);
    }
    for (int i = 0; i < 40; i++) {
        if (libetLazers[i].active) {
            Lazer_Render(&libetLazers[i]);
        }
    }

    LibetConfig* config = (LibetConfig*)data->config;
    static UIElement* bossText = NULL;
    if (!bossText) {
        bossText = UI_CreateText(
            "Libet",
            (SDL_Rect) {
                app.config.screen_width / 2,
                5,
                0,
                0
            },
            (SDL_Color){255, 255, 255, 255},
            1.0f,
            UI_TEXT_ALIGN_CENTER,
            app.resources.textFont
        );
    }
    UI_UpdateText(bossText);
    UI_RenderText(bossText);

    float maxHealthBarWidth = 200.0f;
    float healthBarWidth = 
        ((float) data->state.currentHealth / (float)data->stats.maxHealth) * maxHealthBarWidth;
    if (config->state != LIBET_VINCIBLE) {
        SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 0, 255);
    } else {
        SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    }
    SDL_Rect healthBar = {
        app.config.screen_width / 2 - healthBarWidth / 2,
        20,
        healthBarWidth,
        10
    };
    SDL_RenderFillRect(app.resources.renderer, &healthBar);
}