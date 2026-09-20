#pragma once

#include <stdio.h>
#include "../lib/raylib6/include/raylib.h"
#include "../utils/enums.h"
#include "resourcesloader.h"

#define MAX_SOUNDS 5
#define ALIAS_POOL 3

/* The actual sounds themselves are contained in the "resources" file */
extern Sound soundAliases[MAX_SOUNDS][ALIAS_POOL]; /* Is used to play sounds from gameSounds array */
extern int currentSoundAlias[MAX_SOUNDS];

void LoadAllSounds();
void UnloadAllSounds();
void CreateSound(GameSound soundEnumVal);
Music CreateMusic(GameMusic musicEnumVal, float volume, bool loop);
void StopMusic(GameMusic musicEnumVal);
