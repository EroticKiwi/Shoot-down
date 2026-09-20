#include "../headers/resourcesloader.h"

Texture2D gameTextures[MAX_TEXTURES];
Texture2D gameSprites[MAX_SPRITES];
Sound gameSounds[MAX_SOUNDS];
Music gameMusic[MAX_MUSIC];

void LoadGameTextures()
{
    gameSprites[SPRITE_BOX] = LoadTexture("assets/sprites/box.png");
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
    gameSounds[JUMP_SOUND] = LoadSound("assets/sounds/jump_sound.wav");
    gameSounds[NEWPLATFORM_SOUND] = LoadSound("assets/sounds/newplatform_sound.wav");
    gameSounds[OLDPLATFORM_SOUND] = LoadSound("assets/sounds/oldplatform_sound.wav");
    gameSounds[LOSELIFE_SOUND] = LoadSound("assets/sounds/loselife_sound.wav");
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