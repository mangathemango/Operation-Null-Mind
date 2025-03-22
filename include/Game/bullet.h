/**
 * @file bullet.h
 * @brief Handles bullet functionality, including creation, movement and collision
 * @author Darren
 * @date 2025-03-16
 */
#pragma once

#include <particle_emitterpresets.h>
#include <gun.h>

/**
 * @brief Initializes the bullet system
 * 
 * Sets up initial state for bullet tracking and management.
 */
void Bullet_Start();

/**
 * @brief Updates the state of all active bullets
 * 
 * Handles bullet movement, collision detection and lifetime management.
 */
void Bullet_Update();

/**
 * @brief Renders all active bullets
 * 
 * Draws all currently active bullets to the screen.
 */
void Bullet_Render();