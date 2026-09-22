#pragma once

#include "../utils/structs.h"

#define TOTAL_LEVELS 10
#define POINTS_FOR_CRATES_DESTRUCTION 50
#define POINTS_FOR_DEBRIS_DESTRUCTION 25

#define CRATE_WIDTH 50
#define CRATE_HEIGHT 50
#define MIN_ROTATION 0
#define MAX_ROTATION 359

void Initialize_AllLevels();
bool Is_Level_Locked(int index);
Level Get_Level(int index);
Level Get_Loaded_Level();
void Load_Level(int index);