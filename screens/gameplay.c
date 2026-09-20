#include "gameplay.h"
#include "../headers/level.h"
#include "../utils/structs.h"

bool has_initialized_level;
Level loaded_level;

void Initialize_Level(){
    loaded_level = Get_Loaded_Level();


}

void Display_Gameplay_Screen(){
    
    if(!has_initialized_level){
        Initialize_Level();
    }

}