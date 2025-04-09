#include <enemy_libet.h>
#include <camera.h>
#include <particle_emitterpresets.h>

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
}