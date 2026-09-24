#include "../headers/cutter.h"

void CutTo4Pieces(PhysicsObject originalObj, Vector2 mousePos, PhysicsObject *arr, int arr_starting_point, bool activate_new_phys_objects)
{
    float PW1, PW2 = 0.0f;
    float PH1, PH2 = 0.0f;
    Vector2 newSize[2];
    Vector2 newOrigin;
    Vector2 newGravityMultiplier;
    int rotation;

    PH1 = originalObj.origin.y - originalObj.height / 2;
    PH2 = originalObj.origin.y + originalObj.height / 2;
    PW1 = originalObj.origin.x - originalObj.width / 2;
    PW2 = originalObj.origin.x + originalObj.width / 2;

    newSize[0].y = mousePos.y - PH1;
    newSize[1].y = PH2 - mousePos.y;

    newSize[0].x = mousePos.x - PW1;
    newSize[1].x = PW2 - mousePos.x;

    if (newSize[0].x < 25.0f)
    {
        newSize[0].x = 25.0f;
    }

    if (newSize[1].x < 25.0f)
    {
        newSize[1].x = 25.0f;
    }

    if (newSize[0].y < 25.0f)
    {
        newSize[0].y = 25.0f;
    }

    if (newSize[1].y < 25.0f)
    {
        newSize[1].y = 25.0f;
    }

    /* Top-left */
    newOrigin = (Vector2){mousePos.x - newSize[0].x / 2, mousePos.y - newSize[0].y / 2};
    newGravityMultiplier = (Vector2){originalObj.gravityMultiplier.x - BLAST_FORCE, originalObj.gravityMultiplier.y + BLAST_FORCE};
    rotation = RandomNumberInRange_Inclusive(-360, 360);
    InitializePhysicsObject(&arr[arr_starting_point], newOrigin, newSize[0].x, newSize[0].y, 0, rotation, newGravityMultiplier, activate_new_phys_objects);

    /* Top-right */
    newOrigin = (Vector2){mousePos.x + newSize[1].x / 2, mousePos.y - newSize[0].y / 2};
    newGravityMultiplier = (Vector2){originalObj.gravityMultiplier.x + BLAST_FORCE, originalObj.gravityMultiplier.y + BLAST_FORCE};
    rotation = RandomNumberInRange_Inclusive(-360, 360);
    InitializePhysicsObject(&arr[arr_starting_point + 1], newOrigin, newSize[1].x, newSize[0].y, 0, rotation, newGravityMultiplier, activate_new_phys_objects);

    /* Bottom-left */
    newOrigin = (Vector2){mousePos.x - newSize[0].x / 2, mousePos.y + newSize[1].y / 2};
    newGravityMultiplier = (Vector2){originalObj.gravityMultiplier.x - BLAST_FORCE, originalObj.gravityMultiplier.y - BLAST_FORCE};
    rotation = RandomNumberInRange_Inclusive(-360, 360);
    InitializePhysicsObject(&arr[arr_starting_point + 2], newOrigin, newSize[0].x, newSize[1].y, 0, rotation, newGravityMultiplier, activate_new_phys_objects);

    /* Bottom-right */
    newOrigin = (Vector2){mousePos.x + newSize[1].x / 2, mousePos.y + newSize[1].y / 2};
    newGravityMultiplier = (Vector2){originalObj.gravityMultiplier.x - BLAST_FORCE, originalObj.gravityMultiplier.y - BLAST_FORCE};
    rotation = RandomNumberInRange_Inclusive(-360, 360);
    InitializePhysicsObject(&arr[arr_starting_point + 3], newOrigin, newSize[1].x, newSize[1].y, 0, rotation, newGravityMultiplier, activate_new_phys_objects);
}