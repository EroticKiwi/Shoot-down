#pragma once

#include "../lib/raylib6/include/raylib.h"
#include "../utils/enums.h"

#define MAX_TEXTURES 5
#define MAX_SPRITES 5
#define MAX_SOUNDS 5
#define MAX_MUSIC 1

extern Texture2D gameTextures[MAX_TEXTURES];
extern Texture2D gameSprites[MAX_SPRITES];
extern Sound gameSounds[MAX_SOUNDS];
extern Music gameMusic[MAX_MUSIC];

void LoadGameTextures();
void UnloadGameTextures();
void LoadGameMusic();
void UnloadGameMusic();
void LoadGameSounds();
void UnloadGameSounds();
void LoadAllTextures();
void UnloadAllTextures();