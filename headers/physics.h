#pragma once
#include "screen.h"

#define GRAVITY 9.81
#define GRAVITY_MULTIPLIER_DECREASE_PER_FRAME 3.0f
#define GRAVITY_MULTIPLIER_MIN (-(GRAVITY_MULTIPLIER_DECREASE_PER_FRAME * TARGET_FPS * 2))

/* Returns new position, and updates gravityMultiplier through pointer to Vector2 in parameters */
Vector2 ApplyGravity(Vector2 currentPosition, Vector2 *gravityMultiplier);
void ResetGravity(float *gravityMultiplier);