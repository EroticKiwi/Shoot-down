#include "gameplay.h"
#include "../headers/levels.h"
#include "../utils/structs.h"

bool has_initialized_level;
Level level;

void Initialize_Level(){
    level = Get_Loaded_Level();
}

void Display_Gameplay_Screen(){
    
    if(!has_initialized_level){
        Initialize_Level();
    }

}