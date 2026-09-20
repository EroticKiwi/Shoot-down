#include "../headers/sound.h"

Sound soundAliases[MAX_SOUNDS][ALIAS_POOL]; /* Is used to play sounds from gameSounds array */
int currentSoundAlias[MAX_SOUNDS] = {0};

void LoadAllSounds()
{
    InitAudioDevice();
    LoadGameSounds();
    for (int i = 0; i < MAX_SOUNDS; i++)
    {
        if (gameSounds[i].frameCount > 0)
        {
            for (int j = 0; j < ALIAS_POOL; j++)
            {
                soundAliases[i][j] = LoadSoundAlias(gameSounds[i]);
            }
        }
    }
}

void UnloadAllSounds()
{
    UnloadGameSounds();
    for (int i = 0; i < MAX_SOUNDS; i++)
    {
        for (int j = 0; j < ALIAS_POOL; j++)
        {
            UnloadSoundAlias(soundAliases[i][j]);
        }
    }
    CloseAudioDevice();
}

void CreateSound(GameSound soundEnumVal)
{
    int currentAlias = currentSoundAlias[soundEnumVal];  /* Give me the nth copy of soundEnumVal */
    PlaySound(soundAliases[soundEnumVal][currentAlias]); /* Play the nth alias of soundEnumVal */

    currentSoundAlias[soundEnumVal]++;
    if (currentSoundAlias[soundEnumVal] >= ALIAS_POOL)
        currentSoundAlias[soundEnumVal] = 0;
}

Music CreateMusic(GameMusic musicEnumVal, float volume, bool loop){
    gameMusic[musicEnumVal].looping = loop;
    PlayMusicStream(gameMusic[musicEnumVal]);
    SetMusicVolume(gameMusic[musicEnumVal], volume);
    return gameMusic[musicEnumVal];
}

void StopMusic(GameMusic musicEnumVal){
    StopMusicStream(gameMusic[musicEnumVal]);
}