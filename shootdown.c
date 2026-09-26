#include "lib/raylib6/include/raylib.h"

/* Include headers*/
#include "headers/screen.h"
#include "headers/levels.h"
#include "headers/resourcesloader.h"
#include "headers/sound.h"
/*-----*/

/* Include utils */
#include "utils/enums.h"
/*-----*/

/* Include screens */
#include "screens/main_menu.h"
#include "screens/gameplay.h"
/*-----*/

void DisplayScreen(GameScreen *current_game_screen)
{

    switch (*current_game_screen)
    {
    case MAIN_MENU_SCREEN:
        Display_MainMenu(current_game_screen);
        break;
    case GAMEPLAY_SCREEN:
        Display_Gameplay_Screen(current_game_screen);
        break;
    }
}

void main()
{

    ChangeDirectory(GetApplicationDirectory());

    GameScreen current_game_screen = MAIN_MENU_SCREEN;

    CreateWindow("assets/icon/icon.png", "Shoot Down");

    LoadAllTextures();
    LoadAllSounds();

    Initialize_AllLevels();

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);
        DisplayScreen(&current_game_screen);
        EndDrawing();
    }

    UnloadAllSounds();
    UnloadAllTextures();

    CloseWindow();
}