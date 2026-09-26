#include "../headers/levels.h"
#include "../headers/misc.h"
#include "../headers/screen.h"
#include "../headers/memory_management.h"
#include "../headers/persistence.h"

#include <stdio.h>

Level levels[TOTAL_LEVELS];
bool hasInitializedLevels = false;
int loaded_level = 0;
int max_level_reached = 0;

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
    if (index <= max_level_reached)
    {
        levels[index].locked = false;
    }
    else
    {
        levels[index].locked = true;
    }

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
        min_spawn_pos = (Vector2){0.0f, screenH - 100.0f};
        max_spawn_pos = (Vector2){50.0f, screenH};
        min_gravity_multiplier = (Vector2){200.0f, 400.0f};
        max_gravity_multiplier = (Vector2){375.0f, 650.0f};
        minPoints = 125;
        phys_objs_to_throw = (int)(minPoints / POINTS_FOR_CRATES_DESTRUCTION) + 1 + RandomNumberInRange_Inclusive(3, 6);

        waves = 2;
        waves_starting_points = Memory_Resize(waves_starting_points, waves, sizeof(int));

        waves_starting_points[0] = 0;
        waves_starting_points[1] = phys_objs_to_throw / 2 - 1;

        Create_Level(level, min_gravity_multiplier, max_gravity_multiplier, min_spawn_pos, max_spawn_pos, minPoints, waves, waves_starting_points, phys_objs_to_throw);
        break;
    case 1:
        min_spawn_pos = (Vector2){50.0f, 0.0f};
        max_spawn_pos = (Vector2){screenW - 50.0f, 0.0f};
        min_gravity_multiplier = (Vector2){0.0f, -200.0f};
        max_gravity_multiplier = (Vector2){0.0f, -50.0f};
        minPoints = 250;
        phys_objs_to_throw = (int)(minPoints / POINTS_FOR_CRATES_DESTRUCTION) + 1 + RandomNumberInRange_Inclusive(6, 10);

        waves = 3;
        waves_starting_points = Memory_Resize(waves_starting_points, waves, sizeof(int));

        waves_starting_points[0] = 0;
        waves_starting_points[1] = 4;
        waves_starting_points[2] = 8;

        Create_Level(level, min_gravity_multiplier, max_gravity_multiplier, min_spawn_pos, max_spawn_pos, minPoints, waves, waves_starting_points, phys_objs_to_throw);
        break;
    case 2:
        min_spawn_pos = (Vector2){0.0f, halfScreenH - 50.0f};
        max_spawn_pos = (Vector2){0.0f, halfScreenH + 50.0f};
        min_gravity_multiplier = (Vector2){600.0f, 100.0f};
        max_gravity_multiplier = (Vector2){1200.0f, 400.0f};
        minPoints = 300;
        phys_objs_to_throw = 10;

        waves = 5;
        waves_starting_points = Memory_Resize(waves_starting_points, waves, sizeof(int));

        waves_starting_points[0] = 0;
        waves_starting_points[1] = 1;
        waves_starting_points[2] = 2;
        waves_starting_points[3] = 4;
        waves_starting_points[4] = 6;

        Create_Level(level, min_gravity_multiplier, max_gravity_multiplier, min_spawn_pos, max_spawn_pos, minPoints, waves, waves_starting_points, phys_objs_to_throw);
        break;
    case 3:
        min_spawn_pos = (Vector2){100.0f, 100.0f};
        max_spawn_pos = (Vector2){screenW - 50.0f, screenH - 400.0f};
        min_gravity_multiplier = (Vector2){0.0f, -20.0f};
        max_gravity_multiplier = (Vector2){0.0f, -20.0f};
        minPoints = 400;
        phys_objs_to_throw = 10;

        waves = 2;
        waves_starting_points = Memory_Resize(waves_starting_points, waves, sizeof(int));

        waves_starting_points[0] = 0;
        waves_starting_points[1] = phys_objs_to_throw / 2 - 1;

        Create_Level(level, min_gravity_multiplier, max_gravity_multiplier, min_spawn_pos, max_spawn_pos, minPoints, waves, waves_starting_points, phys_objs_to_throw);
        break;
    case 4:
        min_spawn_pos = (Vector2){halfScreenW - 300.0f, screenH};
        max_spawn_pos = (Vector2){halfScreenW + 300.0f, screenH};
        min_gravity_multiplier = (Vector2){-370.0f, 400.0f};
        max_gravity_multiplier = (Vector2){375.0f, 800.0f};
        minPoints = 400;
        phys_objs_to_throw = (int)(minPoints / POINTS_FOR_CRATES_DESTRUCTION) + 1 + RandomNumberInRange_Inclusive(3, 6);

        waves = 2;
        waves_starting_points = Memory_Resize(waves_starting_points, waves, sizeof(int));

        waves_starting_points[0] = 0;
        waves_starting_points[1] = phys_objs_to_throw / 2 - 1;

        Create_Level(level, min_gravity_multiplier, max_gravity_multiplier, min_spawn_pos, max_spawn_pos, minPoints, waves, waves_starting_points, phys_objs_to_throw);
        break;
    case 5:
        min_spawn_pos = (Vector2){screenW, screenH - 100.0f};
        max_spawn_pos = (Vector2){screenW - 50.0f, screenH};
        min_gravity_multiplier = (Vector2){-700.0f, 400.0f};
        max_gravity_multiplier = (Vector2){-800.0f, 675.0f};
        minPoints = 125;
        phys_objs_to_throw = (int)(minPoints / POINTS_FOR_CRATES_DESTRUCTION) + 1 + RandomNumberInRange_Inclusive(3, 6);

        waves = 2;
        waves_starting_points = Memory_Resize(waves_starting_points, waves, sizeof(int));

        waves_starting_points[0] = 0;
        waves_starting_points[1] = phys_objs_to_throw / 2 - 1;

        Create_Level(level, min_gravity_multiplier, max_gravity_multiplier, min_spawn_pos, max_spawn_pos, minPoints, waves, waves_starting_points, phys_objs_to_throw);
        break;
    case 6:
        min_spawn_pos = (Vector2){0.0f, halfScreenH};
        max_spawn_pos = (Vector2){0.0f, halfScreenH};
        min_gravity_multiplier = (Vector2){2000.0f, 0.0f};
        max_gravity_multiplier = (Vector2){2000.0f, 0.0f};
        minPoints = 50;
        phys_objs_to_throw = 1;

        waves = 1;
        waves_starting_points = Memory_Resize(waves_starting_points, waves, sizeof(int));

        waves_starting_points[0] = 0;

        Create_Level(level, min_gravity_multiplier, max_gravity_multiplier, min_spawn_pos, max_spawn_pos, minPoints, waves, waves_starting_points, phys_objs_to_throw);
        break;
    case 7:
        min_spawn_pos = (Vector2){halfScreenW - 200.0f, screenH};
        max_spawn_pos = (Vector2){halfScreenW + 200.0f, screenH};
        min_gravity_multiplier = (Vector2){-600.0f, 600.0f};
        max_gravity_multiplier = (Vector2){600.0f, 600.0f};
        minPoints = 400;
        phys_objs_to_throw = 12;

        waves = 4;
        waves_starting_points = Memory_Resize(waves_starting_points, waves, sizeof(int));

        waves_starting_points[0] = 0;
        waves_starting_points[1] = 3;
        waves_starting_points[2] = 6;
        waves_starting_points[3] = 9;

        Create_Level(level, min_gravity_multiplier, max_gravity_multiplier, min_spawn_pos, max_spawn_pos, minPoints, waves, waves_starting_points, phys_objs_to_throw);
        break;

    case 8:
        min_spawn_pos = (Vector2){0.0f, halfScreenH - 200.0f};
        max_spawn_pos = (Vector2){0.0f, halfScreenH + 200.0f};
        min_gravity_multiplier = (Vector2){2000.0f, 0.0f};
        max_gravity_multiplier = (Vector2){2000.0f, 0.0f};
        minPoints = 250;
        phys_objs_to_throw = 12;

        waves = 6;
        waves_starting_points = Memory_Resize(waves_starting_points, waves, sizeof(int));

        waves_starting_points[0] = 0;
        waves_starting_points[1] = 2;
        waves_starting_points[2] = 4;
        waves_starting_points[3] = 6;
        waves_starting_points[4] = 8;
        waves_starting_points[5] = 10;

        Create_Level(level, min_gravity_multiplier, max_gravity_multiplier, min_spawn_pos, max_spawn_pos, minPoints, waves, waves_starting_points, phys_objs_to_throw);
        break;

    case 9:
        min_spawn_pos = (Vector2){halfScreenW - 200.0f, halfScreenH + 200.0f};
        max_spawn_pos = (Vector2){halfScreenW + 200.0f, halfScreenH + 400.0f};
        min_gravity_multiplier = (Vector2){-600.0f, 400.0f};
        max_gravity_multiplier = (Vector2){600.0f, -400.0f};
        minPoints = 600;
        phys_objs_to_throw = 30;

        waves = 6;
        waves_starting_points = Memory_Resize(waves_starting_points, waves, sizeof(int));

        waves_starting_points[0] = 0;
        waves_starting_points[1] = 5;
        waves_starting_points[2] = 10;
        waves_starting_points[3] = 15;
        waves_starting_points[4] = 20;
        waves_starting_points[5] = 25;

        Create_Level(level, min_gravity_multiplier, max_gravity_multiplier, min_spawn_pos, max_spawn_pos, minPoints, waves, waves_starting_points, phys_objs_to_throw);
        break;
    }
}

void Initialize_AllLevels()
{

    LoadData_FromFile(&max_level_reached, levels, TOTAL_LEVELS);

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

int Get_Loaded_Level_Index()
{
    return loaded_level;
}

void Load_Level(int index)
{
    loaded_level = index;
}

bool Is_There_A_Next_Level()
{
    if (loaded_level >= TOTAL_LEVELS - 1)
    {
        return false;
    }

    return true;
}

void Reset_Loaded_Level()
{
    loaded_level = 0;
}

int Get_Max_Level_Reached()
{
    return max_level_reached;
}

void Set_Highscore(int newhighscore)
{
    if (newhighscore > levels[loaded_level].highscore)
    {
        levels[loaded_level].highscore = newhighscore;
    }
}

void Save_Levels_Data()
{
    int max_level = max_level_reached;

    if (loaded_level == max_level_reached)
    {
        max_level += 1;
    }

    if (max_level < TOTAL_LEVELS - 1)
    {
        levels[max_level].locked = false;
    }

    SaveData_ToFile(max_level, levels);
}

void Reload_Level_Data()
{
    LoadData_FromFile(&max_level_reached, levels, TOTAL_LEVELS);
}