#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../lib/raylib6/include/raylib.h"
#include "../utils/enums.h"
#include "resourcesloader.h"

/*  [CHARACTER]
    1. Current Sprite
    2. Collider
    3. Other animsprites [Array]
    4. Time each sprite spends on screen (in frames) [Array]
*/

void CreateSprite(GameSprite spriteEnumVal, float width, float height, float posX, float posY, bool mirror, Color color, Rectangle* collider);
void CreateSprite_NoCollider(GameSprite spriteEnumVal, float width, float height, float rotation, float posX, float posY, Color color, bool mirror);
Rectangle CreateSprite_Return(GameSprite spriteEnumVal, float width, float height, float posX, float posY, Color color, bool mirror);