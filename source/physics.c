#include "../headers/physics.h"

void ApplyGravity_Y(float *posX, float *posY, float *gravityMultiplier)
{
    /* We use "-" because to go down it's "+" and to go up it's "-". */
    /* We use "-" here so we can set values elsewhere that to us are more easily comprehensible, without compromising the way coordinates work. */
    *posY = *posY - (*gravityMultiplier * GetFrameTime());

    *gravityMultiplier -= GRAVITY_MULTIPLIER_DECREASE_PER_FRAME;
    // printf("\n gravityMultiplier: %f\n", *gravityMultiplier);
    if (*gravityMultiplier < GRAVITY_MULTIPLIER_MIN)
    {
        *gravityMultiplier = GRAVITY_MULTIPLIER_MIN;
    }
}

void UpdateGravityMultiplier(Vector2 *gravityMultiplier)
{
    if (gravityMultiplier->x < 0)
    {
        gravityMultiplier->x += GRAVITY_MULTIPLIER_DECREASE_PER_FRAME * GetFrameTime();
        if (gravityMultiplier->x > 0)
        {
            gravityMultiplier->x = 0;
        }
    }
    else if (gravityMultiplier->x > 0)
    {
        gravityMultiplier->x -= GRAVITY_MULTIPLIER_DECREASE_PER_FRAME * GetFrameTime();
        if (gravityMultiplier->x < 0)
        {
            gravityMultiplier->x = 0;
        }
    }

    gravityMultiplier->y -= GRAVITY_MULTIPLIER_DECREASE_PER_FRAME; /* Could cause problems when unlocking FPS */
}

float ApplyRotation(float current_rotation, float rotation_speed)
{
    current_rotation += rotation_speed * GetFrameTime();
    return current_rotation;
}

Vector2 ApplyGravity(Vector2 currentPosition, Vector2 *gravityMultiplier)
{
    currentPosition.x = currentPosition.x + (gravityMultiplier->x * GetFrameTime());
    currentPosition.y = currentPosition.y - (gravityMultiplier->y * GetFrameTime());

    UpdateGravityMultiplier(gravityMultiplier);

    return currentPosition;
}

void ResetGravity(float *gravityMultiplier)
{
    *gravityMultiplier = 0;
}
