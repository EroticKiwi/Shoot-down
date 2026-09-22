// #include <stdio.h>
#include "../headers/misc.h"
#include <stdio.h>

bool isRandInitialized = false;

int RandomNumberInRange_Inclusive(int min, int max)
{
    
    if(!isRandInitialized){
        srand(time(NULL));
        isRandInitialized = true;
    }

    int n = rand() % (max - min + 1) + min;
    // printf("\nrandomnumber: %d\n", n);
    return n;
}

void InitializePhysicsObject(PhysicsObject *object, Vector2 origin, float width, float height, float rotation, float rotationSpeed, Vector2 gravityMultiplier)
{
    object->active = true;
    object->origin = origin;
    object->width = width;
    object->height = height;
    object->rotation = rotation;
    object->rotationSpeed = rotationSpeed;
    object->gravityMultiplier = gravityMultiplier;
}