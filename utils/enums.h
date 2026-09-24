#pragma once

/* BASIC UNIVERSAL ENUMS */

typedef enum TextAlign
{
    TOPLEFT = 0,
    TOP = 1,
    TOPRIGHT = 2,
    LEFT = 3,
    CENTER = 4,
    RIGHT = 5,
    BOTTOMLEFT = 6,
    BOTTOM = 7,
    BOTTOMRIGHT = 8
} TextAlign;

typedef enum GameScreen
{
    MAIN_MENU_SCREEN,
    GAMEPLAY_SCREEN
} GameScreen;

typedef enum GameTexture{
    NONE
} GameTexture;

typedef enum GameSprite{
    SPRITE_BOX,
    SPRITE_BOX_PIECE,
    SPRITE_LOCKED,
    SPRITE_WARNING
} GameSprite;

typedef enum GameSound{
    SOUND_BEEP
} GameSound;

typedef enum GameMusic{
    MUSIC
} GameMusic;

/*------------------------------------------*/