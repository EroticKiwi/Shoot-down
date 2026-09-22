#include "../headers/levels.h"
#include "../headers/misc.h"
#include "../headers/screen.h"
#include "../headers/memory_management.h"

#include <stdio.h>

Level levels[TOTAL_LEVELS];
bool hasInitializedLevels = false;
int loaded_level;

void Create_Level(Level *level, Vector2 min_gravity_multiplier, Vector2 max_gravity_multiplier, Vector2 min_spawn_pos, Vector2 max_spawn_pos, int min_points, int waves, int *waves_starting_points, int phys_objs_to_throw)
{
    level->minPoints = min_points;
    level->min_gravity_multiplier = min_gravity_multiplier;
    level->max_gravity_multiplier = max_gravity_multiplier;
    level->min_spawn_pos = min_spawn_pos;
    level->max_spawn_pos = max_spawn_pos;
    level->waves = waves;
    level->waves_starting_points = waves_starting_points;
    level->phys_objs_to_throw = phys_objs_to_throw;
}

void Initialize_SingleLevel(Level *level, int index)
{
    /* Check with persistence! */
    level->locked = true; // check with memory persistence
    level->highscore = 0; // check with memory persistence
    //-------

    Vector2 min_gravity_multiplier;
    Vector2 max_gravity_multiplier;
    Vector2 min_spawn_pos;
    Vector2 max_spawn_pos;
    int minPoints;
    int waves;
    int *waves_starting_points;
    int phys_objs_to_throw;

    switch (index)
    {
    case 0:
        min_gravity_multiplier = (Vector2){200.0f, 400.0f};
        max_gravity_multiplier = (Vector2){375.0f, 650.0f};
        min_spawn_pos = (Vector2){0.0f, screenH - 100.0f};
        max_spawn_pos = (Vector2){50.0f, screenH};
        minPoints = 125;
        phys_objs_to_throw = (int)(minPoints / POINTS_FOR_CRATES_DESTRUCTION) + 1 + RandomNumberInRange_Inclusive(3, 6);

        waves = 2;
        waves_starting_points = Memory_Create(waves_starting_points, waves, sizeof(int));

        waves_starting_points[0] = 0;
        waves_starting_points[1] = phys_objs_to_throw / 2 - 1;

        Create_Level(level, min_gravity_multiplier, max_gravity_multiplier, min_spawn_pos, max_spawn_pos, minPoints, waves, waves_starting_points, phys_objs_to_throw);
        break;
    }
}

void Initialize_AllLevels()

{

    for (int i = 0; i < TOTAL_LEVELS; i++)
    {
        Initialize_SingleLevel(&levels[i], i);
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

Level Get_Loaded_Level()
{
    return levels[loaded_level];
}

void Load_Level(int index)
{
    loaded_level = index;
}