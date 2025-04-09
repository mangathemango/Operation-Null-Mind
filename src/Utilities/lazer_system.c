#include <vec2.h>
#include <colliders.h>
#include <player.h>
#include <math.h>
#include <camera.h>
#include <app.h>
#include <lazer_system.h>

/**
 * @brief Updates the lazer's position and handles collisions
 *
 * @param lazer Pointer to the Lazer struct containing its properties
 */
void Lazer_Update(Lazer* lazer) {
    Vec2 currentPosition = lazer->startPosition;
    Collider lazerCollider = {
        .active = true,
        .hitbox = Vec2_ToSquareRect(currentPosition, 1),
        .collidesWith = COLLISION_LAYER_ENVIRONMENT
    };

    Collider_Register(&lazerCollider, NULL);

    for (int i = 0; i < 2000; i++) {
        if (Vec2_AreEqual(lazer->direction, Vec2_Zero)) {
            break;
        }

        ColliderCheckResult result;
        bool hitSomething = false;
        Collider_Check(&lazerCollider, &result);

        for (int j = 0; j < result.count; j++) {
            if (result.objects[j]->layer == COLLISION_LAYER_PLAYER && lazer->damage > 0) {
                Player_TakeDamage(lazer->damage);
            }
            hitSomething = true;
            break;
        }

        if (hitSomething) {
            break;
        }

        Vec2_Increment(&currentPosition, lazer->direction);
        lazerCollider.hitbox = Vec2_ToSquareRect(currentPosition, 1);
    }

    Collider_Reset(&lazerCollider);
    lazer->endPosition = currentPosition;
}

/**
 * @brief Renders a lazer with a glowing effect
 *
 * @param lazer Pointer to the Lazer struct containing its properties
 */
void Lazer_Render(Lazer* lazer) {
    // Draw the red outer glow
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 0, 0, 255);
    Vec2 lazerStart = Camera_WorldVecToScreen(lazer->startPosition);
    Vec2 lazerEnd = Camera_WorldVecToScreen(lazer->endPosition);

    for (int dx = -lazer->width; dx <= lazer->width; dx++) {
        for (int dy = -lazer->width; dy <= lazer->width; dy++) {
            if ((dx == 0 && dy == 0) || (dx * dx + dy * dy > lazer->width * lazer->width)) {
                continue;
            }

            SDL_RenderDrawLine(
                app.resources.renderer,
                lazerStart.x + dx,
                lazerStart.y + dy,
                lazerEnd.x + dx,
                lazerEnd.y + dy
            );
        }
    }

    // Draw the white center line
    if (lazer->width > 0) {
        SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    }
    SDL_RenderDrawLine(
        app.resources.renderer,
        lazerStart.x,
        lazerStart.y,
        lazerEnd.x,
        lazerEnd.y
    );
}