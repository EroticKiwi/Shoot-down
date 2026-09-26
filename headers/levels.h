#pragma once

#include "../utils/structs.h"

#define TOTAL_LEVELS 10
#define POINTS_FOR_CRATES_DESTRUCTION 50
#define POINTS_FOR_DEBRIS_DESTRUCTION 25

#define CRATE_WIDTH 75
#define CRATE_HEIGHT 75
#define MIN_ROTATION -360
#define MAX_ROTATION 360

void Initialize_AllLevels();
bool Is_Level_Locked(int index);
Level Get_Level(int index);
Level Get_Loaded_Level();
int Get_Loaded_Level_Index();
void Load_Level(int index);
bool Is_There_A_Next_Level();
void Reset_Loaded_Level();
int Get_Max_Level_Reached();
void Set_Highscore(int newhighscore);
void Save_Levels_Data();
void Reload_Level_Data();