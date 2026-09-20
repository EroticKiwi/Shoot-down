#include "../headers/screen.h"

int screenW;
int screenH;
int halfScreenW;
int halfScreenH;

void SetRuntimeIcon(char *imagePath)
{
    Image icon = LoadImage(imagePath);
    ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    SetWindowIcon(icon);
    UnloadImage(icon);
}

void CreateWindow(char *iconPath, char *windowName)
{

    InitWindow(DEBUGSCREENW, DEBUGSCREENH, windowName); /* screenW and screenH are calculated based on the OPEN window! Using (0,0) tells raylib to open the biggest window it can */

    screenW = GetScreenWidth();
    screenH = GetScreenHeight();
    halfScreenW = screenW / 2;
    halfScreenH = screenH / 2;

    SetTargetFPS(TARGET_FPS);

    if (iconPath)
    {
        SetRuntimeIcon(iconPath);
    }
}

void CreateText(char *text, int fontSize, Color fontColor, int posX, int posY, int paddingX, int paddingY)
{

    int textHeigth = fontSize;
    int halfTextHeigth = textHeigth / 2;
    int textWidth = MeasureText(text, fontSize);
    int halfTextWidth = textWidth / 2;

    posX = posX - halfTextWidth + paddingX;
    posY = posY - halfTextHeigth + paddingY;

    DrawText(text, posX, posY, fontSize, fontColor);
}

void CreateTextAligned(char *text, int fontSize, Color fontColor, TextAlign alignment)
{

    /* GENERAL RULES */
    /*
        The "position" of text is set by its anchor point, that would the the top left corner of it.
        If we want to put text somewhere on the screen we would have to get said position
        and then subtract half the text width otherwise the text would only START at that position, not be in that position
        the way we intend it to.

        Things change if we intend to put text at the right edge of the screen, though.
        If that were the case we would get the position of the edge of the screen and then we would NOT subtract half the text width,
        we would subtract the WHOLE text width otherwise we'd have half the text out of the screen since the position our center would be
        located at would be exactly the edge of the screen.

        Of course, you CANNOT center text at the borders of the window, that would cut the text in half.
        That goes for both text width and text height.
    */

    int posX = 0;
    int posY = 0;

    int padding = 10;

    int textHeight = fontSize;
    int halfTextHeigth = textHeight / 2;
    int textWidth = MeasureText(text, fontSize);
    int halfTextWidth = (textWidth / 2);

    switch (alignment)
    {
    case TOP:
        posX = halfScreenW - halfTextWidth;
        posY = padding;
        break;
    case TOPRIGHT:
        posX = screenW - textWidth - padding;
        posY = padding;
        break;
    case LEFT:
        posX = padding;
        posY = halfScreenH - halfTextHeigth;
        break;
    case CENTER:
        posX = halfScreenW - halfTextWidth;
        posY = halfScreenH - halfTextHeigth;
        break;
    case RIGHT:
        posX = screenW - textWidth - padding;
        posY = halfScreenH - halfTextHeigth;
        break;
    case BOTTOMLEFT:
        posY = screenH - textHeight - padding;
        posX = padding;
        break;
    case BOTTOM:
        posX = halfScreenW - halfTextWidth;
        posY = screenH - textHeight - padding;
        break;
    case BOTTOMRIGHT:
        posX = screenW - textWidth - padding;
        posY = screenH - textHeight - padding;
        break;
    }

    DrawText(text, posX, posY, fontSize, fontColor);
}

void CreateTextFromInt(int number, int fontSize, Color fontColor, int posX, int posY, int paddingX, int paddingY)
{

    const char *text = TextFormat("%d", number);

    int textHeigth = fontSize;
    int halfTextHeigth = textHeigth / 2;
    int textWidth = MeasureText(text, fontSize);
    int halfTextWidth = textWidth / 2;

    posX = posX - halfTextWidth + paddingX;
    posY = posY - halfTextHeigth + paddingY;

    DrawText(text, posX, posY, fontSize, fontColor);
}

void CreateImage(GameTexture textureEnumVal, int scale, int posX, int posY, int paddingX, int paddingY)
{
    Texture2D texture = gameTextures[textureEnumVal];

    float width = texture.width * scale;
    float height = texture.height * scale;

    float drawX = posX - (width / 2) + paddingX;
    float drawY = posY - (height / 2) + paddingY;

    Vector2 pos = {drawX, drawY};

    DrawTextureEx(texture, pos, 0, scale, WHITE);
}

void CreateImageWithSize(GameTexture textureEnumVal, float width, float height, int posX, int posY, int paddingX, int paddingY)
{
    Texture2D texture = gameTextures[textureEnumVal];

    Rectangle sourceRectangle = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Rectangle destinationRectangle = {
        (float)posX + paddingX,
        (float)posY + paddingY,
        width,
        height};

    Vector2 origin = {width / 2.0f, height / 2.0f};

    DrawTexturePro(texture, sourceRectangle, destinationRectangle, origin, 0.0f, WHITE);
}

void CreateRectangle(float width, float height, float rotation, Color color, int posX, int posY, int paddingX, int paddingY)
{
    int drawX = posX - (width / 2) + paddingX;
    int drawY = posY - (height / 2) + paddingY;

    Rectangle rect = (Rectangle){
        posX,
        posY,
        width,
        height
    };

    Vector2 origin = (Vector2){
        width/2,
        height/2
    };

    //DrawRectangle(drawX, drawY, width, height, color);
    DrawRectanglePro(rect, origin, rotation, color);
}

void CreateRectangleWithText(char *buttonText, int fontSize, Color fontColor, int width, int height, Color rectangleColor, int posX, int posY, int paddingX, int paddingY)
{

    int drawX = posX - (width / 2) + paddingX;
    int drawY = posY - (height / 2) + paddingY;

    DrawRectangle(drawX, drawY, width, height, rectangleColor);

    int textHeigth = fontSize;
    int halfTextHeigth = textHeigth / 2;
    int textWidth = MeasureText(buttonText, fontSize);
    int halfTextWidth = textWidth / 2;

    posX = posX - halfTextWidth + paddingX;
    posY = posY - halfTextHeigth + paddingY;

    DrawText(buttonText, posX, posY, fontSize, fontColor);
}

void CreateRectangleWithText_Adaptive(char *buttonText, int fontSize, Color fontColor, Color rectangleColor, int posX, int posY, int paddingX, int paddingY)
{

    int textHeigth = fontSize;
    int halfTextHeigth = textHeigth / 2;
    int textWidth = MeasureText(buttonText, fontSize);
    int halfTextWidth = textWidth / 2;

    int width = textWidth + 5;
    int height = textHeigth + 15;

    int drawX = posX - (width / 2) + paddingX;
    int drawY = posY - (height / 2) + paddingY;

    DrawRectangle(drawX, drawY, width, height, rectangleColor);

    posX = posX - halfTextWidth + paddingX;
    posY = posY - halfTextHeigth + paddingY;

    DrawText(buttonText, posX, posY, fontSize, fontColor);
}

void CreateButton_Rectangle(char *buttonText, int fontSize, Color fontColor, int width, int height, Color buttonColor, int posX, int posY, int paddingX, int paddingY, bool *trigger, bool *hover, bool *hold)
{
    if (trigger != NULL)
        *trigger = false;
    if (hover != NULL)
        *hover = false;
    if (hold != NULL)
        *hold = false;

    int drawX = posX - (width / 2) + paddingX;
    int drawY = posY - (height / 2) + paddingY;

    Rectangle bounds = {
        (float)drawX,
        (float)drawY,
        (float)width,
        (float)height};

    Vector2 mousePosition = GetMousePosition();

    if (CheckCollisionPointRec(mousePosition, bounds))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        { /* button click */
            if (trigger != NULL)
                *trigger = true;
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        { /* hold button */
            if (hold != NULL)
                *hold = true;
        }
        else
        { /* hover */
            if (hover != NULL)
                *hover = true;
        }
    }

    DrawRectangle(drawX, drawY, width, height, buttonColor);

    int textWidth = MeasureText(buttonText, fontSize);
    int textX = bounds.x + (bounds.width / 2) - (textWidth / 2);
    int textY = bounds.y + (bounds.height / 2) - (fontSize / 2);

    DrawText(buttonText, textX, textY, fontSize, fontColor);
}

void CreateButton_Image(GameTexture textureEnumVal, float width, float height, int posX, int posY, int paddingX, int paddingY, bool *trigger, bool *hover, bool *hold)
{
    if (trigger != NULL)
        *trigger = false;
    if (hover != NULL)
        *hover = false;
    if (hold != NULL)
        *hold = false;

    Texture2D texture = gameTextures[textureEnumVal];

    Rectangle sourceRectangle = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Rectangle destinationRectangle = {
        (float)posX + paddingX,
        (float)posY + paddingY,
        width,
        height};

    Vector2 origin = {width / 2.0f, height / 2.0f};

    Vector2 mousePosition = GetMousePosition();

    Rectangle collisionRectangle = {
        destinationRectangle.x - origin.x,
        destinationRectangle.y - origin.y,
        destinationRectangle.width,
        destinationRectangle.height};

    if (CheckCollisionPointRec(mousePosition, collisionRectangle))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        { /* button click */
            if (trigger != NULL)
                *trigger = true;
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        { /* hold button */
            if (hold != NULL)
                *hold = true;
        }
        else
        { /* hover */
            if (hover != NULL)
                *hover = true;
        }
    }

    DrawTexturePro(texture, sourceRectangle, destinationRectangle, origin, 0.0f, WHITE);
}

bool CreateButton_Image_Return(GameTexture textureEnumVal, float width, float height, int posX, int posY, int paddingX, int paddingY)
{
    Texture2D texture = gameTextures[textureEnumVal];

    Rectangle sourceRectangle = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Rectangle destinationRectangle = {
        (float)posX + paddingX,
        (float)posY + paddingY,
        width,
        height};

    Vector2 origin = {width / 2.0f, height / 2.0f};

    Vector2 mousePosition = GetMousePosition();

    DrawTexturePro(texture, sourceRectangle, destinationRectangle, origin, 0.0f, WHITE);

    Rectangle collisionRectangle = {
        destinationRectangle.x - origin.x,
        destinationRectangle.y - origin.y,
        destinationRectangle.width,
        destinationRectangle.height};

    if (CheckCollisionPointRec(mousePosition, collisionRectangle))
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        { /* button click */
            return true;
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        { /* hold button */
        }
        else
        { /* hover */
        }
    }

    return false;
}