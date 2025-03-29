/**
 * @file echo_update.c
 * @brief Implements update logic for Echo enemy type
 *
 * Contains the AI behavior and state updates for the Echo enemy,
 * which uses a teleportation-based movement pattern.
 *
 * @author Mango
 * @date 2025-03-06
 */

#include <enemy_kamikaze.h>
#include <player.h>
#include <time_system.h>
#include <random.h>
#include <circle.h>
#include <sound.h>

/**
 * @brief [PostUpdate] Updates the Echo enemy's state
 * 
 * This function is called each frame to update the Echo enemy's behavior,
 * including its teleportation movement pattern and attack logic.
 * 
 * @param data Pointer to the enemy data structure
 */
void Kamikaze_Update(EnemyData* data) {
    if (data->state.isDead) return;
    KamikazeConfig *config = data->config;

    if (config->exploding) {
        config->explosionTimer += Time->deltaTimeSeconds;
        if (config->explosionTimer >= config->explosionTime) {
            KamikazeExplosionEmitter->position = data->state.position;
            ParticleEmitter_ActivateOnce(KamikazeExplosionEmitter);
            if (Vec2_Distance(data->state.position, player.state.position) < config->explosionRadius) {
                Player_TakeDamage(data->stats.damage);
            }

            Sound_Play_Effect(SOUND_VINE_BOOM);
            free(data->config);
            Enemy_HandleDeath(data);
            return;
        }
        return;
    }



    config->directionChangeTime -= Time->deltaTimeSeconds;
    if (config->directionChangeTime <= 0) {
        config->directionChangeTime = RandFloat(0.2f, 1.0f);
        data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));
        data->state.direction = Vec2_RotateDegrees(data->state.direction, RandFloat(-90, 90));
    }
    if (Vec2_Distance(data->state.position, player.state.position) < 100) {
        data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));
        if (config->directionChangeTime <= 0) {
            config->directionChangeTime = RandFloat(0.2f, 0.3f);
            data->state.direction = Vec2_RotateDegrees(data->state.direction, RandFloat(-30, 30));
        }
    }
    if (Vec2_Distance(data->state.position, player.state.position) < 50) {
        Animation_Play(data->resources.animation, "explode");
        data->stats.maxSpeed = 0;
        config->exploding = true;
    }
}