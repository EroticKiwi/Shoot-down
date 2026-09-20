#include "../headers/sprites.h"

void CreateSprite_NoCollider(GameSprite spriteEnumVal, float width, float height, float rotation, float posX, float posY, Color color, bool mirror){
    Texture2D spriteTexture = gameSprites[spriteEnumVal];

    /* 1. Calculate position */
    Vector2 spriteOrigin = {width/2, height/2}; /* origin */

    /* 2. Create Rectangle (Image) */
    Rectangle spriteRect = {0.0f, 0.0f, (float)spriteTexture.width, (float)spriteTexture.height}; /* source */
    Rectangle spritePosition = {posX, posY, width, height}; /* destination */

    /* 2.1 Mirror if needed */
    if(mirror){
        spriteRect.width = -spriteRect.width;
    }
    
    /* 3. Draw Texture */
    DrawTexturePro(spriteTexture, spriteRect, spritePosition, spriteOrigin, rotation, color);
}

void CreateSprite(GameSprite spriteEnumVal, float width, float height, float posX, float posY, bool mirror, Color color, Rectangle* collider){

    Texture2D spriteTexture = gameSprites[spriteEnumVal];

    /* 1. Calculate position */
    Vector2 spriteOrigin = {width/2, height/2}; /* origin */

    /* 2. Create Rectangle (Image) */
    Rectangle spriteRect = {0.0f, 0.0f, (float)spriteTexture.width, (float)spriteTexture.height}; /* source */
    Rectangle spritePosition = {posX, posY, width, height}; /* destination */

    /* 2.1 Mirror if needed */
    if(mirror){
        spriteRect.width = -spriteRect.width;
    }

    /* 2.5 Create Rectangle (Collider) */
    *collider = (Rectangle){spritePosition.x - spriteOrigin.x, spritePosition.y - spriteOrigin.y, width, height};
    
    /* 3. Draw Texture */
    DrawTexturePro(spriteTexture, spriteRect, spritePosition, spriteOrigin, 0.0f, color);
}

Rectangle CreateSprite_Return(GameSprite spriteEnumVal, float width, float height, float posX, float posY, Color color, bool mirror){

    Texture2D spriteTexture = gameSprites[spriteEnumVal];

    /* 1. Calculate position */
    Vector2 spriteOrigin = {width/2, height/2}; /* origin */

    /* 2. Create Rectangle (Image) */
    Rectangle spriteRect = {0.0f, 0.0f, (float)spriteTexture.width, (float)spriteTexture.height}; /* source */
    Rectangle spritePosition = {posX, posY, width, height}; /* destination */

    /* 2.1 Mirror if needed */
    if(mirror){
        spriteRect.width = -spriteRect.width;
    }

    /* 2.5 Create Rectangle (Collider) */
    Rectangle spriteCollider = {spritePosition.x - spriteOrigin.x, spritePosition.y - spriteOrigin.y, width, height};
    
    /* 3. Draw Texture */
    DrawTexturePro(spriteTexture, spriteRect, spritePosition, spriteOrigin, 0.0f, color);
    
    /* Return collider */
    return spriteCollider;
}