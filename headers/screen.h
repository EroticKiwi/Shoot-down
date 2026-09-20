#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../lib/raylib6/include/raylib.h"
#include "../utils/enums.h"
#include "../headers/resourcesloader.h"

#define DEBUGSCREENW 1280
#define DEBUGSCREENH 720
#define TARGET_FPS 120

extern int screenW;
extern int screenH;
extern int halfScreenW;
extern int halfScreenH;

void CreateWindow(char *iconPath, char *windowName);
void CreateText(char *text, int fontSize, Color fontColor, int posX, int posY, int paddingX, int paddingY);
void CreateTextAligned(char *text, int fontSize, Color fontColor, TextAlign alignment);
void CreateTextFromInt(int number, int fontSize, Color fontColor, int posX, int posY, int paddingX, int paddingY);
void CreateImage(GameTexture textureEnumVal, int scale, int posX, int posY, int paddingX, int paddingY);
void CreateImageWithSize(GameTexture textureEnumVal, float width, float height, int posX, int posY, int paddingX, int paddingY);
void CreateRectangle(float width, float height, float rotation, Color color, int posX, int posY, int paddingX, int paddingY);
void CreateRectangleWithText(char *buttonText, int fontSize, Color fontColor, int width, int height, Color rectangleColor, int posX, int posY, int paddingX, int paddingY);
void CreateRectangleWithText_Adaptive(char *buttonText, int fontSize, Color fontColor, Color rectangleColor, int posX, int posY, int paddingX, int paddingY);
void CreateButton_Rectangle(char *buttonText, int fontSize, Color fontColor, int width, int height, Color buttonColor, int posX, int posY, int paddingX, int paddingY, bool *trigger, bool *hover, bool *hold);
void CreateButton_Image(GameTexture textureEnumVal, float width, float height, int posX, int posY, int paddingX, int paddingY, bool *trigger, bool *hover, bool *hold);
bool CreateButton_Image_Return(GameTexture textureEnumVal, float width, float height, int posX, int posY, int paddingX, int paddingY);
