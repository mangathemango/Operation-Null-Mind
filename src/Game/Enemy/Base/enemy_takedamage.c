/**
 * @file enemy_takedamage.c
 * @brief Handles enemy damage and health
 *
 * Implements the damage processing system for enemies,
 * including health reduction and death checks.
 *
 * @author Mango
 * @date 2025-03-04
 */

#include <enemy.h>
#include <player.h>
#include <stdio.h>

UIElement* EnemyHealthTexts[ENEMY_MAX * 10] = {NULL};
#include <player.h>

/**
 * @brief [Utility] Applies damage to an enemy
 * 
 * Reduces an enemy's health based on the damage amount. Enemies with
 * 0 or less health after damage will be marked for death processing.
 * 
 * @param enemy Pointer to the enemy to damage
 * @param damage Amount of damage to apply
 */
void Enemy_TakeDamage(EnemyData* enemy, int damage) {
    if (enemy->state.isDead) return;
    int effectiveDamage = damage * (100 - player.resources.skillResources.armoredUpDamageOutputDamageReduction) / 100;
    enemy->state.currentHealth -= effectiveDamage;
    Enemy_CreateHealthText(enemy, effectiveDamage);
}

void Enemy_CreateHealthText(EnemyData* enemy, int damage) {
    if (enemy->state.isDead) return;
    
    char textBuffer[50];
    snprintf(textBuffer, sizeof(textBuffer), "-%d", damage);
    UIElement* text = UI_CreateText(
        textBuffer, 
        Vec2_ToSquareRect(
            Camera_WorldVecToScreen(
                (Vec2) {
                    enemy->state.position.x, 
                    enemy->state.position.y - enemy->animData.spriteSize.y / 2
                }
            ), 
            0
        ),
        (SDL_Color) {255, 255, 255, 255},
        1.0f,
        UI_TEXT_ALIGN_CENTER,
        app.resources.textFont
    );
    for (int i = 0; i < ENEMY_MAX * 10; i++) {
        if (EnemyHealthTexts[i] == NULL) {
            EnemyHealthTexts[i] = text;
            break;
        }
    }
}

void Enemy_UpdateHealthTexts() {
    for (int i = 0; i < ENEMY_MAX * 10; i++) {
        if (EnemyHealthTexts[i] == NULL) continue;
        EnemyHealthTexts[i]->rect.y -= 5.0f * Time->deltaTimeSeconds;
        int nextAlpha = EnemyHealthTexts[i]->color.a - 1000 * Time->deltaTimeSeconds;
        if (nextAlpha <= 0) {
            nextAlpha = 0;
            UI_DestroyText(EnemyHealthTexts[i]);
            EnemyHealthTexts[i] = NULL;
            continue;
        }
        UI_ChangeTextColor( 
            EnemyHealthTexts[i], 
            (SDL_Color) {
                255, 
                255, 
                255, 
                nextAlpha
            }
        );
        UI_UpdateText(EnemyHealthTexts[i]);
    }
}

void Enemy_RenderHealthTexts() {
    for (int i = 0; i < ENEMY_MAX * 10; i++) {
        if (EnemyHealthTexts[i] == NULL) continue;
        UI_RenderText(EnemyHealthTexts[i]);
    }
}

