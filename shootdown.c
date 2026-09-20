#include "lib/raylib6/include/raylib.h"

/* Include headers*/
#include "headers/screen.h"
#include "headers/levels.h"
#include "headers/resourcesloader.h"
/*-----*/

/* Include utils */
#include "utils/enums.h"
/*-----*/

/* Include screens */
#include "screens/main_menu.h"
/*-----*/

void DisplayScreen(GameScreen *current_game_screen){

    switch(*current_game_screen){
        case MAIN_MENU_SCREEN:
            Display_MainMenu(current_game_screen);
        break;
    }

}

void main(){

    ChangeDirectory(GetApplicationDirectory());

    GameScreen current_game_screen = MAIN_MENU_SCREEN;

    CreateWindow(NULL, "Shoot Down");

    LoadAllTextures();

    Initialize_AllLevels();

    while(!WindowShouldClose()){
        
        BeginDrawing();
            ClearBackground(BLACK);
            DisplayScreen(&current_game_screen);
        EndDrawing();

    }

    CloseWindow();
}