#pragma once

#include <stdio.h>
#include "../lib/raylib6/include/raylib.h"
#include "../lib/raylib6/include/raymath.h"
#include "../utils/structs.h"
#include "../utils/enums.h"

/* Calculates and sets the corret min and max vertexes for the given collider */
/* Needs to be called every frame for all the colliders currently active */
void UpdateCollider(PhysicsObject *obj);
void UpdateColliders(PhysicsObject *objects, int objects_length);
bool CheckCollision(PhysicsObject A, PhysicsObject B);
bool CheckMouseOverlap_Single(Vector2 mousePosition, PhysicsObject object);
int CheckMouseOverlap_Multiple(Vector2 mousePosition, PhysicsObject *objects, int* collisionInfo, int objects_length);