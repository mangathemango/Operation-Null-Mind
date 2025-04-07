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

/**
 * @brief [Utility] Initiates player dash movement if conditions are met
 * 
 * Activates the dash ability if off cooldown and player has directional input.
 * Plays dash sound effect and locks direction during dash.
 * 
 * @return int Status code (0 for success)
 * 
 * @todo [player_skills.c:24] Change dash sfx
 */
int Player_Dash() {
    // Doesn't dash when idle
    if (Vec2_Magnitude(player.state.direction) == 0) return 0;
    if (player.state.movementLocked) return 0;
    if (!Timer_IsFinished(player.resources.dashCooldownTimer)) return 0;
    
    Sound_Play_Effect(SOUND_DASH); // Play dash sound effect
    player.state.dashing = true; 
    player.state.directionLocked = true; // Player can't control movement during dash

    Timer_Start(player.resources.dashCooldownTimer);
    Timer_Start(player.resources.dashDurationTimer);
    return 0;
}

/**
 * @brief [Utility] Processes player dash state and effects
 * 
 * This is called every frame player.state.dashing is true.
 * Updates dash particle effects and handles dash movement.
 * 
 * @return int Status code (0 for success)
 */
int Player_HandleDash() {
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
        return 0;
    }
    if (Timer_IsFinished(player.resources.dashDurationTimer) && insideEnemy) player.state.directionLocked = false;
    // Update dash particles
    float timeLeft = Timer_GetTimeLeft(player.resources.dashDurationTimer) / player.stats.dashDuration;
    player.resources.dashParticleEmitter->position = player.state.position;
    player.resources.dashParticleEmitter->direction = Vec2_RotateDegrees(player.state.direction, 180);
    player.resources.dashParticleEmitter->particleSpeed = 200 * timeLeft + 200;
    ParticleEmitter_ActivateOnce(player.resources.dashParticleEmitter);

    player.state.currentSpeed = player.stats.dashSpeed;
    return 0;
}


bool LastStand()
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
            Sound_Play_Effect(1);
            return true;
        }
    }

    return false;
}

int overPressured()
{
    if(player.state.skillState.overPressured == true)
    {
        player.resources.skillResources.overPressuredBulletConsumptionMultipler = player.stats.skillStat.overPressuredOriginalMultipler;
        player.resources.skillResources.overPressuredFireRate = player.stats.skillStat.overPressuredOriginalFireRate;
        player.resources.skillResources.overPressuredProjectileSpeed = player.stats.skillStat.overPressuredOriginalProjectileSpeed;
        return 1;
    }
    else 
    {
        player.resources.skillResources.overPressuredBulletConsumptionMultipler = 1;
        player.resources.skillResources.overPressuredFireRate = 1;
        player.resources.skillResources.overPressuredProjectileSpeed = 1;
    }
    return 0;
}

void scavenger()
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

void hemocycle()
{
    static bool JustHealed = false;
    if(player.state.skillState.hemoCycle == true)
    {
        if(player.stats.enemiesKilled % 4 == 0 && JustHealed == false)
        {
            JustHealed = true;
            player.state.currentHealth += player.stats.skillStat.hemocycleHealthGained;
            if(player.state.currentHealth > player.stats.maxHealth) player.state.currentHealth = player.stats.maxHealth;
            SDL_Log("Hemocycle: %d", player.stats.skillStat.hemocycleHealthGained);
        }
        else if(player.stats.enemiesKilled % 4 != 0)
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

void armoredUp()
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

bool kineticArmor()
{
    if(player.state.skillState.kineticArmor == true)
    {
        if (player.state.currentAmmo < 20) return 1;
        bool randomizer = RandInt(0,1);
        if(randomizer == 0)
        {
            player.state.currentAmmo -= 20;
        }
        SDL_Log("Kinetic Armor: %d", randomizer);
        return randomizer;
    }

    else
    {
        return 1;
    }
}

bool ghostLoad()
{
    int randomizer = RandInt(1,10);
    if(player.state.skillState.ghostLoad == true)
    {
        if(player.resources.skillResources.ammoShoot % 8 == 0 && player.resources.skillResources.ammoShoot != 0)
        {
            SDL_Log("Ghost Load mweh");
            if(randomizer == 1)
            {
                player.resources.skillResources.ghostLoadRandomizer = player.stats.skillStat.ghostLoadRandomizer;
                SDL_Log("Gun jammed");
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

void Skill_Update()
{
    LastStand();
    overPressured();
    scavenger();
    hemocycle();
    armoredUp();
   // i call kinetic armor where player gets damaged.
   //i call ghostload when player shoots.
}

/**
 * @brief [Utility] Activates the Crashout skill, sacrificing health for damage
 * 
 * Takes 25% of the player's current health and gives a 2x damage multiplier
 * for 15 seconds. Has a cooldown before it can be used again.
 * 
 * @return int Status code (0 for success, 1 for on cooldown)
 */
int Player_CrashOut() {
    // Don't activate if already active or on cooldown
    if (player.state.skillState.crashOut) return 1;
    if (!Timer_IsFinished(player.resources.skillResources.crashOutCooldown)) return 1;
    SDL_Log("Player_Crashout Activated");
    
    // Calculate health cost (25% of current health)
    int healthCost = player.state.currentHealth * 0.25f;
    
    // Ensure player has enough health to use this ability (at least 5 HP left)
    if (player.state.currentHealth - healthCost < 10) {
        player.state.currentHealth = 10;
    }
    else {
        player.state.currentHealth -= healthCost;
    }
    
    player.state.skillState.crashOut = true; // Activate crashout state
    
    // Activate skill effects
    // player.state.crashoutActive = true;
    // player.state.crashoutMultiplier = 2.0f;  // 2x damage multiplier
    
    // Start timers
    Timer_Start(player.resources.skillResources.crashOutDuration);
    
    // Play effect
    Sound_Play_Effect(SOUND_BOOST_UP);  // Use an appropriate sound

    
    // Create visual effect (red glow around player)

    
    return 0;
}

/**
 * @brief [Update] Handles the Crashout skill state and effects
 * 
 * Updates visual effects, checks duration, and resets state when completed.
 * 
 * @return int Status code (0 for success)
 */
int Player_HandleCrashOut() {
    if (!player.state.skillState.crashOut) return 0;
    

    // Check if duration has expired
    if (Timer_IsFinished(player.resources.skillResources.crashOutDuration)) {
        // Reset state
        player.state.skillState.crashOut = false;
        
        // Start cooldown
        Timer_Start(player.resources.skillResources.crashOutCooldown);

        Sound_Play_Effect(SOUND_BOOST_DOWN); // Use an appropriate sound
        
        player.stats.skillStat.crashOutCurrentMultipler = 1.0f; // Reset damage multiplier
        
        return 0;
    }
    
    player.stats.skillStat.crashOutCurrentMultipler = player.state.skillState.crashOutMultiplier; // Maintain damage multiplier while active
    player.resources.crashOut->position = player.state.position;
    ParticleEmitter_ActivateOnce(player.resources.crashOut);
    SDL_Log("Player_Crashout Active");
    
    return 0;
}

int Parry()
{
    //Check if parry is active
    if(player.state.skillState.parryActive == true)return 1;
    if(!Timer_IsFinished(player.resources.skillResources.parryTimer)) return 1;
    
    //Starting timers and changing state
    player.state.skillState.parryActive = true;
    Timer_Start(player.resources.skillResources.parryDurationTimer);
    SDL_Log("Parry Activated");

    //Finding mouseDirection
    Vec2 mouseWorldPosition = Camera_ScreenVecToWorld(Input->mouse.position);
    Vec2 mouseDirection = Vec2_Normalize(Vec2_Subtract(mouseWorldPosition, player.state.position));
    

    player.resources.skillResources.parryDirection = mouseDirection;
    player.resources.skillResources.parryRadius = 0;
    SDL_Log("Parry is active");
    return 0;
}

void Handle_ParryBullets()
{
    
}

int Handle_ParryRender()
{
    //Handles the rendered half circle
    Vec2 mouseDirection = player.resources.skillResources.parryDirection;

    player.resources.skillResources.parryTexture = CreateHalfCircleOutlineTexture(100 , mouseDirection, (SDL_Color){3, 252, 232, 255}, 4);
    player.resources.skillResources.parryRadius += Timer_GetTimeLeft(player.resources.skillResources.parryDurationTimer);
    float radius =  15 * player.resources.skillResources.parryRadius; //Because the radius is in time, if the game lags the radius actually gets smaller xd

        
    SDL_Rect dest = Vec2_ToCenteredSquareRect(
        Camera_WorldVecToScreen(player.state.position), // Position of the circle
        radius
     ); 

    SDL_RenderCopy(app.resources.renderer, player.resources.skillResources.parryTexture, NULL, &dest);
    
}

int Handle_Parry()
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

    //Finding mouseDirection
    Vec2 mouseDirection = player.resources.skillResources.parryDirection;

    //Iterate through all the enemies
    for(int i = 0; i < ENEMY_MAX;i++)
    {
        EnemyData* enemy = &enemies[i];
        if(enemy->state.isDead == true) continue;
        GunData* gun = NULL;
        if (enemy->type == ENEMY_TYPE_ECHO) {
            EchoConfig* config = enemy->config;
            gun = &config->gun;
        } 
        else if(enemy->type == ENEMY_TYPE_JUGGERNAUT)
        {
            JuggernautConfig* config = enemy->config;
            gun = &config->gun;
        }
        else if(enemy->type == ENEMY_TYPE_TACTICIAN)
        {
            TacticianConfig* config = enemy->config;
            gun = &config->gun;
        }
        else if(enemy->type == ENEMY_TYPE_RADIUS)
        {
            RadiusConfig* config = enemy->config;
            gun = &config->gun;
        }
        else if(enemy->type == ENEMY_TYPE_PROXY)
        {
            ProxyConfig* config = enemy->config;
            gun = &config->gun;
        }
        else if(enemy->type == ENEMY_TYPE_SABOT)
        {
            SabotConfig* config = enemy->config;
            gun = &config->gun;
        }
        else continue;

        if (!gun) continue;

        //Iterate through all the bullets
        for(int i = 0;i < gun->resources.bulletPreset->maxParticles; i++)
        {
            Particle* bullet = &gun->resources.bulletPreset->particles[i];
            if(!bullet->alive) continue;
            //Check if the bullet is in the parry range
            if(Vec2_Distance(player.state.position, bullet->position) >= 1000) continue; //THIS SHOULD BE 50
            
            //Finding bulletDirection
            Vec2 bulletDirection = Vec2_Normalize(Vec2_Subtract(bullet->position, player.state.position));
            SDL_Log("Bullet Parried");
        
            //Finding angle
            int angle = Vec2_AngleBetween(mouseDirection, bulletDirection);
            SDL_Log("Angle: %d", angle);

            //Check if the angle is within the parry range
            if(player.stats.skillStat.maxParryAngle < abs(angle)) continue;

            //Parry the bullet
            bullet->direction = bulletDirection;

            //Changing the colliders
            bullet->collider->collidesWith |= COLLISION_LAYER_ENEMY;
        }
    }

    ParticleEmitter_Update(player.resources.skillResources.parryParticleEmitter);

    return 0;
}