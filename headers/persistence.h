#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "levels.h"

#define SAVE_FILE_NAME "gamedata.txt"
#define STUDIO_NAME "EroticKiwi"
#define GAME_NAME "Shoot Down"

void Write_To_File(char path[], int max_level_reached,  const Level levels[]);
void Load_From_File(char path[], int *max_level_reached, Level *levels, int levels_length);
void SaveData_ToFile(int max_level_reached, const Level levels[]);
void LoadData_FromFile(int *max_level_reached, Level *levels, int levels_length);