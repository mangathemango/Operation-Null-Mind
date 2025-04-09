#include <vec2.h>
#include <SDL.h>

typedef struct {
    bool active;
    Vec2 startPosition;
    Vec2 direction;      // Direction of the lazer
    Vec2 endPosition;
    int width;         // Width of the lazer
    int damage;
} Lazer;

/**
 * @brief Updates the lazer's position and handles collisions
 *
 * @param startPosition The starting position of the lazer
 * @param direction The direction of the lazer
 * @param damage The damage the lazer deals to the player (if not zero)
 * @return Vec2 The end position of the lazer after collision or reaching max distance
 */
void Lazer_Update(Lazer* lazer);

/**
 * @brief Renders a lazer with a glowing effect
 *
 * @param startPosition The starting position of the lazer
 * @param endPosition The ending position of the lazer
 * @param width The width of the lazer
 */
void Lazer_Render(Lazer* lazer);