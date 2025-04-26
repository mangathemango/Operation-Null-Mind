/**
 * @file player_skills.c
 * @brief Implements player special abilities and skills
 *
 * Handles the activation, cooldown and effects of player skills
 * such as dashing, special attacks, and other abilities.
 *
 * @author Mango
 * @date 2025-03-05
 */

// Written by Mango and Darren on 05/03/2025

#include <player.h>
#include <time_system.h>
#include <timer.h>
#include <sound.h>
#include <camera.h>
#include <random.h>
#include <gun.h>
#include <bullet.h>
#include <enemy_types.h>
#include <input.h>
#include <stdlib.h>
#include <circle.h>
#include <math.h>

void Player_UpdateSkill()
{
    Player_HandleLastStandActive();
    Player_HandleOverpressuredActive();
    Player_HandleScavengerActive();
    Player_HandleHemocycleActive();
    Player_HandleArmoredUpActive();
   // i call kinetic armor where player gets damaged.
   //i call ghostload when player shoots.
}

/**
 * @brief [Utility] Initiates player dash movement if conditions are met
 * 
 * Activates the dash ability if off cooldown and player has directional input.
 * Plays dash sound effect and locks direction during dash.
 * 
 * @todo [player_skills.c:24] Change dash sfx
 */
void Player_Dash() {
    // Doesn't dash when idle
    if (Vec2_Magnitude(player.state.direction) == 0) return;
    if (player.state.movementLocked) return;
    if (!Timer_IsFinished(player.resources.dashCooldownTimer)) return;
    SDL_Log("Dashing\n");   
    Sound_Play_Effect(SOUND_DASH); // Play dash sound effect
    player.state.dashing = true; 
    player.state.directionLocked = true; // Player can't control movement during dash

    Timer_Start(player.resources.dashCooldownTimer);
    Timer_Start(player.resources.dashDurationTimer);
}

/**
 * @brief [Utility] Processes player dash state and effects
 * 
 * This is called every frame player.state.dashing is true.
 * Updates dash particle effects and handles dash movement.
 */
void Player_HandleDash() {
    player.state.collider.layer = COLLISION_LAYER_NONE;
    // Ends the dash state when the timer is finished
    ColliderCheckResult result;
    Collider_Check(&player.state.collider, &result);
    bool insideEnemy = false;
    for (int i = 0; i < result.count; i++){
        if (result.objects[i]->layer & COLLISION_LAYER_ENEMY){
            insideEnemy = true;
            break;
        }
    }
    if (Timer_IsFinished(player.resources.dashDurationTimer) && !insideEnemy)
    {
        player.state.dashing = false; //Just unchecks dashing
        player.state.directionLocked = false; //Just unchecks movementlock
        player.state.collider.layer = COLLISION_LAYER_PLAYER;
        return;
    }
    if (Timer_IsFinished(player.resources.dashDurationTimer) && insideEnemy) player.state.directionLocked = false;
    // Update dash particles
    float timeLeft = Timer_GetTimeLeft(player.resources.dashDurationTimer) / player.stats.dashDuration;
    player.resources.dashParticleEmitter->position = player.state.position;
    player.resources.dashParticleEmitter->direction = Vec2_RotateDegrees(player.state.direction, 180);
    player.resources.dashParticleEmitter->particleSpeed = 200 * timeLeft + 200;
    ParticleEmitter_ActivateOnce(player.resources.dashParticleEmitter);

    player.state.currentSpeed = player.stats.dashSpeed;
}


void Player_HandleLastStandActive()
{
    if(player.state.skillState.lastStand == true)
    {
        static bool lastStandActive = false;
        if(player.state.currentHealth <= 0 && !lastStandActive)
        {
            player.state.currentHealth = player.stats.maxHealth;
            lastStandActive = true;
            player.state.skillState.lastStand = false;
            Timer_Start(player.resources.INVINCIBLE_Timer);
            Sound_Play_Effect(SOUND_LAST_STAND);
        }
    }
}

void Player_HandleOverpressuredActive()
{
    if(player.state.skillState.overPressured == true)
    {
        player.resources.skillResources.overPressuredFireRate = player.stats.skillStat.overPressuredOriginalFireRate;
        player.resources.skillResources.overPressuredProjectileSpeed = player.stats.skillStat.overPressuredOriginalProjectileSpeed;
    }
    else 
    {
        player.resources.skillResources.overPressuredFireRate = 1;
        player.resources.skillResources.overPressuredProjectileSpeed = 1;
    }
}

void Player_HandleScavengerActive()
{
    if(player.state.skillState.scavenger == true)
    {
        player.resources.skillResources.scavengerAmmoBonus = player.stats.skillStat.scavengerAmmoBonus;
        player.stats.maxAmmo = 200 * (100 - player.stats.skillStat.scavengerAmmoCapacity) / 100;
    }
    else
    {
        player.resources.skillResources.scavengerAmmoBonus = 0;
        player.stats.maxAmmo = 200;
    }
}

void Player_HandleHemocycleActive()
{
    static bool JustHealed = false;
    if(player.state.skillState.hemoCycle == true)
    {
        if(player.stats.enemiesKilled % 10 == 0 && JustHealed == false)
        {
            JustHealed = true;
            player.state.currentHealth += player.stats.skillStat.hemocycleHealthGained;
            if(player.state.currentHealth > player.stats.maxHealth) player.state.currentHealth = player.stats.maxHealth;
        }
        else if(player.stats.enemiesKilled % 10 != 0)
        {
            JustHealed = false;
        }

        player.resources.skillResources.hemocycleMultipler = player.stats.skillStat.hemocycleMultipler;
    }


    else 
    {
        player.resources.skillResources.hemocycleMultipler = 0;
    }
}

void Player_HandleArmoredUpActive()
{
    if(player.state.skillState.armoredUp == true)
    {
        player.resources.skillResources.armoredUpIncomingDamageReduction = player.stats.skillStat.armoredUpIncomingDamageReduction;
        player.resources.skillResources.armoredUpDamageOutputDamageReduction = player.stats.skillStat.armoredUpDamageOutputDamageReduction;
    }
    else
    {
        player.resources.skillResources.armoredUpIncomingDamageReduction = 0;
        player.resources.skillResources.armoredUpDamageOutputDamageReduction = 0;
    }
}

bool Player_KineticArmorIsEffective()
{
    if(player.state.skillState.kineticArmor == true)
    {
        if (player.state.currentAmmo < 20) return 1;
        bool randomizer = RandInt(0,1);
        if(randomizer == 0)
        {
            player.state.currentAmmo -= 20;
        }
        return randomizer;
    }

    else
    {
        return 1;
    }
}

bool Player_GhostLoadGunJammed()
{
    int randomizer = RandInt(1,10);
    if(player.state.skillState.ghostLoad == true)
    {
        if(player.resources.skillResources.ammoShoot % 4 == 0 && player.resources.skillResources.ammoShoot != 0)
        {
            if(randomizer == 1)
            {
                player.resources.skillResources.ghostLoadRandomizer = player.stats.skillStat.ghostLoadRandomizer;
            }
            else
            {
                player.resources.skillResources.ghostLoadRandomizer = 0;
            }
            return true;
        }
        else
        {
            player.resources.skillResources.ghostLoadRandomizer = 0;
            return false;
        }
    }
    else
    {
        player.resources.skillResources.ghostLoadRandomizer = 0;
        return false;
    }
}


int Player_Parry()
{
    //Check if parry is active
    if(player.state.skillState.parryActive == true)return 1;
    if(!Timer_IsFinished(player.resources.skillResources.parryTimer)) return 1;
    Sound_Play_Effect(SOUND_PARRY); // Play parry sound effect
    //Starting timers and changing state
    player.state.skillState.parryActive = true;
    Timer_Start(player.resources.skillResources.parryDurationTimer);

    //Finding mouseDirection
    Vec2 mouseWorldPosition = Camera_ScreenVecToWorld(Input->mouse.position);
    Vec2 mouseDirection = Vec2_Normalize(Vec2_Subtract(mouseWorldPosition, player.state.position));
    

    player.resources.skillResources.parryDirection = mouseDirection;
    player.resources.skillResources.parryRadius = 0;

    mouseDirection = player.resources.skillResources.parryDirection;

    ParticleEmitter* bulletEmitters[7] = {
        EchoBulletEmitter,
        SabotBulletEmitter,
        JuggernautBulletEmitter,
        LibetBulletEmitter,
        TacticianBulletEmitter,
        ProxyBulletEmitter,
        RadiusBulletEmitter
    };
    //Iterate through all the enemies
    for(int i = 0; i < 7;i++)
    {
        ParticleEmitter* bulletEmitter = bulletEmitters[i];
        if (!bulletEmitter) continue; // Skip if bulletEmitter is NULL
        bool sfxPlayed = false;
        //Iterate through all the bullets
        for(int i = 0; i < bulletEmitter->maxParticles; i++)
        {
            Particle* bullet = &bulletEmitter->particles[i];
            if(!bullet->alive) continue;
            //Check if the bullet is in the parry range
            if(Vec2_Distance(player.state.position, bullet->position) >= 70) continue; //THIS SHOULD BE 50
            
            //Finding bulletDirection
            Vec2 bulletDirection = Vec2_Normalize(Vec2_Subtract(bullet->position, player.state.position));
            
            //Finding angle
            int angle = Vec2_AngleBetween(mouseDirection, bulletDirection);

            //Check if the angle is within the parry range
            if(player.stats.skillStat.maxParryAngle < abs(angle)) continue;

            //Parry the bullet
            bullet->direction = bulletDirection;
            bullet->speed = 600.0f; //This is the speed of the bullet, it should be 700.0f
            //Changing the colliders
            bullet->collider->collidesWith = COLLISION_LAYER_ENEMY | COLLISION_LAYER_ENVIRONMENT;
            bullet->color = (SDL_Color){255, 255, 0, 255};
            if (!sfxPlayed) {
                sfxPlayed = true;
                // Play parry sound effect
                Sound_Play_Effect(SOUND_HITMARKER);
            }
            player.state.skillState.parryHit = true;
            player.resources.skillResources.parryParticleEmitter->position = bullet->position;
            ParticleEmitter_ActivateOnce(player.resources.skillResources.parryParticleEmitter);
        }
    }

    ParticleEmitter_Update(player.resources.skillResources.parryParticleEmitter);
    return 0;
}



int Player_ParryRenderCircleVFX()
{
    //Handles the rendered half circle
    Vec2 mouseDirection = player.resources.skillResources.parryDirection;


    player.resources.skillResources.parryTexture = CreateHalfCircleOutlineTexture(100 , mouseDirection, (SDL_Color){3, 252, 232, 255}, 10);
    
    player.resources.skillResources.parryRadius += 1000.0f * Time->deltaTimeSeconds; //This is the speed of the parry radius growing, it should be 700.0f
    float radius =  player.resources.skillResources.parryRadius; //Because the radius is in time, if the game lags the radius actually gets smaller xd

    // Set opacity based on time left
    SDL_SetTextureAlphaMod(
        player.resources.skillResources.parryTexture, 
        255 * 
        Timer_GetTimeLeft(player.resources.skillResources.parryDurationTimer) 
        / player.stats.skillStat.parryDuration
    );

    SDL_Rect dest = Vec2_ToCenteredSquareRect(
        Camera_WorldVecToScreen(player.state.position), // Position of the circle
        radius
     ); 

    SDL_RenderCopy(app.resources.renderer, player.resources.skillResources.parryTexture, NULL, &dest);
    return 0;
}

int Player_HandleParry()
{
    
    //Check if parry is active
    if(!player.state.skillState.parryActive) return 1;
    //Deactivate parry after the timer is finished
    if(Timer_IsFinished(player.resources.skillResources.parryDurationTimer))
    {
        player.state.skillState.parryActive = false;
        Timer_Start(player.resources.skillResources.parryTimer);
        return 1;
    }

    return 0;
}