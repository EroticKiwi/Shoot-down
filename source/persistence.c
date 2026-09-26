#include "../headers/persistence.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

/* DON'T SHIFT+ALT+F ON THIS FILE, IT MESSES UP THE INDENTATION! */

void Write_To_File(char path[], int max_level_reached, const Level levels[])
{
    FILE *file_to_save_to = fopen(path, "w");
    if (file_to_save_to == NULL)
    {
        printf("\nFILE ERROR: Couldn't write to save file!\n");
        return;
    }

    fprintf(file_to_save_to, "MAX_LEVEL_REACHED: %d", max_level_reached);
    for (int i = 0; i < max_level_reached; i++)
    {
        fprintf(file_to_save_to, "\n%d", levels[i].highscore);
    }

    fclose(file_to_save_to);
    printf("\nFILE SUCCESS: Successfully saved data to save file!\n");
}

void Load_From_File(char path[], int *max_level_reached, Level *levels, int levels_length)
{

    *max_level_reached = 0;

    FILE *file_to_read_from = fopen(path, "r");
    if (file_to_read_from == NULL)
    {
        printf("\nFILE ERROR: Couldn't read from save file!\n");
        return;
    }

    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file_to_read_from) != NULL)
    {
        sscanf(buffer, "MAX_LEVEL_REACHED: %d", max_level_reached);
    }

    int i = 0;

    while (fgets(buffer, sizeof(buffer), file_to_read_from) != NULL && i < levels_length)
    {
        sscanf(buffer, "%d", &levels[i].highscore);
        i++;
    }

    fclose(file_to_read_from);
    printf("\nFILE SUCCESS: Successfully loaded data from save file!\n");
}

void SaveData_ToFile(int max_level_reached, const Level levels[])
{

    char dir[512];

#ifdef _WIN32
    char *appdata = getenv("LOCALAPPDATA");
    char studio_folder_path[256];
    snprintf(studio_folder_path, sizeof(studio_folder_path), "%s\\%s", appdata, STUDIO_NAME);
    _mkdir(studio_folder_path);

    char gamename_folder_path[256];
    snprintf(gamename_folder_path, sizeof(gamename_folder_path), "%s\\%s", studio_folder_path, GAME_NAME);
    _mkdir(gamename_folder_path);

    char savefile_path[256];
    snprintf(savefile_path, sizeof(savefile_path), "%s\\%s", gamename_folder_path, SAVE_FILE_NAME);

    snprintf(dir, sizeof(dir), "%s", savefile_path);

#elif defined(__APPLE__)
    char *home = getenv("HOME");
    char studio_folder_path[256];
    snprintf(studio_folder_path, sizeof(studio_folder_path), "%s/Library/Application Support/%s", home, STUDIO_NAME);
    mkdir(studio_folder_path, 0777);

    char gamename_folder_path[256];
    snprintf(gamename_folder_path, sizeof(gamename_folder_path), "%s/%s", studio_folder_path, GAME_NAME);
    mkdir(gamename_folder_path, 0777);

    char savefile_path[256];
    snprintf(savefile_path, sizeof(savefile_path), "%s/%s", gamename_folder_path, SAVE_FILE_NAME);

    snprintf(dir, sizeof(dir), "%s", savefile_path);

#elif defined(__linux__)
    char *home = getenv("HOME");
    char studio_folder_path[256];
    snprintf(studio_folder_path, sizeof(studio_folder_path), "%s/.local/share/%s", home, STUDIO_NAME);
    mkdir(studio_folder_path, 0777);

    char gamename_folder_path[256];
    snprintf(gamename_folder_path, sizeof(gamename_folder_path), "%s/%s", studio_folder_path, GAME_NAME);
    mkdir(gamename_folder_path, 0777);

    char savefile_path[256];
    snprintf(savefile_path, sizeof(savefile_path), "%s/%s", gamename_folder_path, SAVE_FILE_NAME);

    snprintf(dir, sizeof(dir), "%s", savefile_path);

#endif

    Write_To_File(dir, max_level_reached, levels);
}

void LoadData_FromFile(int *max_level_reached, Level *levels, int levels_length)
{
    char dir[512];

#ifdef _WIN32
    char *appdata = getenv("LOCALAPPDATA");
    char studio_folder_path[256];
    snprintf(studio_folder_path, sizeof(studio_folder_path), "%s\\%s", appdata, STUDIO_NAME);

    char gamename_folder_path[256];
    snprintf(gamename_folder_path, sizeof(gamename_folder_path), "%s\\%s", studio_folder_path, GAME_NAME);

    char savefile_path[256];
    snprintf(savefile_path, sizeof(savefile_path), "%s\\%s", gamename_folder_path, SAVE_FILE_NAME);

    snprintf(dir, sizeof(dir), "%s", savefile_path);

#elif defined(__APPLE__)
    char *home = getenv("HOME");
    char studio_folder_path[256];
    snprintf(studio_folder_path, sizeof(studio_folder_path), "%s/Library/Application Support/%s", home, STUDIO_NAME);

    char gamename_folder_path[256];
    snprintf(gamename_folder_path, sizeof(gamename_folder_path), "%s/%s", studio_folder_path, GAME_NAME);

    char savefile_path[256];
    snprintf(savefile_path, sizeof(savefile_path), "%s/%s", gamename_folder_path, SAVE_FILE_NAME);

    snprintf(dir, sizeof(dir), "%s", savefile_path);

#elif defined(__linux__)
    char *home = getenv("HOME");
    char studio_folder_path[256];
    snprintf(studio_folder_path, sizeof(studio_folder_path), "%s/.local/share/%s", home, STUDIO_NAME);

    char gamename_folder_path[256];
    snprintf(gamename_folder_path, sizeof(gamename_folder_path), "%s/%s", studio_folder_path, GAME_NAME);

    char savefile_path[256];
    snprintf(savefile_path, sizeof(savefile_path), "%s/%s", gamename_folder_path, SAVE_FILE_NAME);

    snprintf(dir, sizeof(dir), "%s", savefile_path);

#endif

    Load_From_File(dir, max_level_reached, levels, levels_length);
}