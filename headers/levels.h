#pragma once

#include "../utils/structs.h"

#define TOTAL_LEVELS 10
#define POINTS_FOR_CRATES_DESTRUCTION 50
#define POINTS_FOR_DEBRIS_DESTRUCTION 25

#define STARTING_MIN_POINTS 200;

void Initialize_AllLevels();
bool Is_Level_Locked(int index);
Level Get_Level(int index);
Level Get_Loaded_Level();
void Load_Level(int index);