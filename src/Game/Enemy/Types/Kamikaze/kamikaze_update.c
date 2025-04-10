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

    switch (config->state) {
    
    // In walking state, kamikaze moves in a random direction
    // Switches to charging state if the player is within 100 pixels
    case KAMIKAZE_STATE_WALKING:

        config->directionChangeTime -= Time->deltaTimeSeconds;
        if (config->directionChangeTime <= 0) {
            // Changes direction every 0.2 to 1 second
            config->directionChangeTime = RandFloat(0.2f, 1.0f);

            // Randomly changes direction to 90 degrees left or right to the player
            // This is to make the kamikaze move in a random direction, but still towards the player
            data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));
            data->state.direction = Vec2_RotateDegrees(data->state.direction, RandFloat(-90, 90));
        }

        // Switch to charging state if the player is within 100 pixels
        if (Vec2_Distance(data->state.position, player.state.position) < 100) 
            config->state = KAMIKAZE_STATE_CHARGING;
        break;


    // In charging state, kamikaze moving direction is a lot more towards the player
    // Switches to exploding state if the player is within 50 pixels
    case KAMIKAZE_STATE_CHARGING:

        config->directionChangeTime -= Time->deltaTimeSeconds;
        if (config->directionChangeTime <= 0) {
            // Changes direction every 0.2 to 0.3 second
            config->directionChangeTime = RandFloat(0.2f, 0.3f);

            // Randomly changes direction to 30 degrees left or right to the player
            data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));
            data->state.direction = Vec2_RotateDegrees(data->state.direction, RandFloat(-30, 30));
        }

        if (Vec2_Distance(data->state.position, player.state.position) < 50) {
            config->state = KAMIKAZE_STATE_EXPLODING;
        }

        break;

    // Exploding state is when kamikaze is about to boom boom
    // Most of the logic happening in this "state" is handled in kamikaze_render
    // This one only handles the ACTUAL explosion, not the ABOUT TO explosion.
    case KAMIKAZE_STATE_EXPLODING:
        // Stop moving
        data->stats.maxSpeed = 0;
        config->explosionTimer += Time->deltaTimeSeconds * data->state.tacticianBuff;

        if (config->explosionTimer >= config->explosionTime) {
            // Handles ACTUAL kamikaze explosion
            KamikazeExplosionEmitter->position = data->state.position;
            ParticleEmitter_ActivateOnce(KamikazeExplosionEmitter);

            if (Vec2_Distance(data->state.position, player.state.position) < config->explosionRadius) {
                Player_TakeDamage(data->stats.damage);
            }
            Sound_Play_Effect(SOUND_EXPLOSION);
            free(data->config);
            data->state.currentHealth = 0;
            data->state.isDead = true;
            Collider_Reset(&data->state.collider);
            data->config = NULL;
        }
        break;
    }
    

}