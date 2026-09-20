#pragma once

#include <stdlib.h>
#include "../utils/structs.h"
#include <time.h>

int RandomNumberInRange_Inclusive(int min, int max);
void InitializePhysicsObject(PhysicsObject *object, Vector2 origin, float width, float height, float rotation, float rotationSpeed, Vector2 gravityMultiplier);
