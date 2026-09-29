#include "../headers/resourcesloader.h"

Texture2D gameTextures[MAX_TEXTURES];
Texture2D gameSprites[MAX_SPRITES];
Sound gameSounds[MAX_SOUNDS];
Music gameMusic[MAX_MUSIC];

void LoadGameTextures()
{
    gameSprites[SPRITE_BOX] = LoadTexture("assets/sprites/box.png");
    gameSprites[SPRITE_BOX_PIECE] = LoadTexture("assets/sprites/box-piece.png");
    gameSprites[SPRITE_LOCKED] = LoadTexture("assets/sprites/locked.png");
    gameSprites[SPRITE_WARNING] = LoadTexture("assets/sprites/warning.png");
}

void UnloadGameTextures()
{
    for (int i = 0; i < MAX_TEXTURES; i++)
    {
        UnloadTexture(gameTextures[i]);
    }

    for (int i = 0; i < MAX_SPRITES; i++)
    {
        UnloadTexture(gameSprites[i]);
    }
}

void LoadGameMusic()
{
    gameMusic[MUSIC] = LoadMusicStream("assets/music/bgmusic.mp3");
}

void UnloadGameMusic()
{
    for (int i = 0; i < MAX_MUSIC; i++)
    {
        UnloadMusicStream(gameMusic[i]);
    }
}

void LoadGameSounds()
{
    gameSounds[SOUND_BEEP] = LoadSound("assets/sfx/beep.wav");
    gameSounds[SOUND_COUNT] = LoadSound("assets/sfx/count.wav");
    gameSounds[SOUND_APPEAR] = LoadSound("assets/sfx/appear.wav");
    gameSounds[SOUND_DESTROY] = LoadSound("assets/sfx/destroy.wav");
    gameSounds[SOUND_DEBRIS] = LoadSound("assets/sfx/debris.wav");
    LoadGameMusic();
}

void UnloadGameSounds()
{
    for (int i = 0; i < MAX_SOUNDS; i++)
    {
        UnloadSound(gameSounds[i]);
    }
}

void LoadAllTextures()
{
    LoadGameTextures();
}

void UnloadAllTextures()
{
    UnloadGameTextures();
}