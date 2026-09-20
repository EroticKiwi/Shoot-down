#include "../headers/levels.h"
#include "../headers/misc.h"

#include <stdio.h>

Level levels[TOTAL_LEVELS];
bool hasInitializedLevels = false;
int loaded_level;

void Initialize_SingleLevel(Level *level, int minPoints)
{
    level->locked = true; // check with memory persistence
    level->highscore = 0; // check with memory persistence
    level->minPoints = minPoints;
    level->phys_objs_to_throw = (int)(minPoints / POINTS_FOR_CRATES_DESTRUCTION) + 1 + RandomNumberInRange_Inclusive(3, 6);
}

void Initialize_AllLevels()
{
    int minPoints = STARTING_MIN_POINTS;
    for (int i = 0; i < TOTAL_LEVELS; i++)
    {
        Initialize_SingleLevel(&levels[i], minPoints);
        minPoints *= 1.5f;
    }

    levels[0].locked = false;

    hasInitializedLevels = true;
}

bool Is_Level_Locked(int index)
{
    if (!hasInitializedLevels)
    {
        Initialize_AllLevels();
    }

    if (index < 0 || index >= TOTAL_LEVELS)
    {
        printf("\nWARNING: THE INDEX FOR GETLEVEL IS NOT VALID! RETURNING LEVEL 0!\n");
        return levels[0].locked;
    }

    return levels[index].locked;
}

Level Get_Level(int index)
{

    if (!hasInitializedLevels)
    {
        Initialize_AllLevels();
    }

    if (index < 0 || index >= TOTAL_LEVELS)
    {
        printf("\nWARNING: THE INDEX FOR GETLEVEL IS NOT VALID! RETURNING LEVEL 0!\n");
        return levels[0];
    }

    return levels[index];
}

Level Get_Loaded_Level(){
    return levels[loaded_level];
}

void Load_Level(int index){
    loaded_level = index;
}