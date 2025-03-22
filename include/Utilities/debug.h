/**
 * @file debug.h
 * @brief This file contains the debug rendering functions.
 *
 * These functions are used to render debug information to the screen,
 * such as hitboxes, FPS count, and other debug information.
 *
 * @author Mango
 * @date 2025-03-01
 */

#pragma once
#include <SDL.h>
#include <player.h>
#include <app.h>

/**
 * @brief Renders the hitboxes of game objects.
 */
void Debug_RenderHitboxes();

/**
 * @brief Renders the current FPS count.
 */
void Debug_RenderFPSCount();

/**
 * @brief Renders the current spike count.
 */
void Debug_RenderSpikeCount();

/**
 * @brief Renders information about the current chunk.
 */
void Debug_RenderCurrentChunk();