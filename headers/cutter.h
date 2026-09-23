#pragma once

#include "../lib/raylib6/include/raylib.h"
#include "../utils/enums.h"
#include "misc.h"

#define BLAST_FORCE 100.0f

void CutTo4Pieces(PhysicsObject originalObj, Vector2 mousePos, PhysicsObject *arr, int arr_starting_point, bool activate_new_phys_objects);