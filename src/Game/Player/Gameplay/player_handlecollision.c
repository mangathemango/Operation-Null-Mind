#include <player.h>
#include <colliders.h>

bool Player_DetectCollision() {
    ColliderCheckResult collisions;

    // This Collider_Check call will fill the collisions variable with all the colliders that the player is colliding with.
    // For more information, hover over Collider_Check in VSCode to view the function definition.
    if (!Collider_Check(&player.state.collider, &collisions)) return false;

    // The collisions array can then be looped through to check for specific layers.
    for (int i = 0; i < collisions.count; i ++) {
        if (collisions.objects[i]->layer == COLLISION_LAYER_ENVIRONMENT) {
            return true;
        }
        if (collisions.objects[i]->layer == COLLISION_LAYER_ENEMY && !player.state.dashing) {
            return true;
        }
    }
    return false;
}