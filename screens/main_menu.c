#include "main_menu.h"
#include "../utils/structs.h"
#include "../utils/enums.h"
#include "../headers/animations.h"
#include "../headers/levels.h"
#include "../headers/sprites.h"

#include <string.h>

#define TITLE_POS ((Vector2){halfScreenW, halfScreenH - (START_BUTTON_SIZE.y / 2)})
#define TITLE_SIZE 32.0f
#define START_BUTTON_POS ((Vector2){TITLE_POS.x, TITLE_POS.y + START_BUTTON_SIZE.y + 25.0f})
#define START_BUTTON_SIZE ((Vector2){200.0f, 75.0f})
#define START_BUTTON_TEXT_SIZE 32.0f

#define LEVELSELECT_TITLE_POS ((Vector2){halfScreenW, halfScreenH - (TOTAL_LEVELS / LEVEL_COLS) * LEVEL_BUTTON_SIZE.y / 2.0f})
#define LEVELSELECT_TITLE_SIZE 32.0f

#define ENDLESS_BUTTON_SIZE ((Vector2){200.0f, 75.0f})
#define ENDLESS_BUTTON_TEXT_SIZE 24.0f

#define LEVEL_BUTTON_STARTING_X (halfScreenW - (LEVEL_BUTTON_SIZE.x * (int)LEVEL_COLS / 2) + LEVEL_BUTTON_SIZE.x / 4)
#define LEVEL_BUTTON_STARTING_Y (LEVELSELECT_TITLE_POS.y + LEVEL_BUTTON_SIZE.y)
#define LEVEL_BUTTON_SIZE ((Vector2){50.0f, 50.0f})
#define LEVEL_BUTTON_UNFINISHED_COLOR ORANGE
#define LEVEL_BUTTON_FINISHED_COLOR BLUE
#define LEVEL_BUTTON_LOCKED_COLOR GRAY

#define LEVEL_COLS 5

bool hasInitialized = false;
AnimatableButton startBtn;

bool showLevelSelect = false;
AnimatableButton endlessBtn;
AnimatableButton level_buttons[TOTAL_LEVELS];

bool hasFetchedLevelStatus = false;
bool levelStatus[TOTAL_LEVELS];

void InitializeVariables()
{
    AnimatableButton _startBtn = {
        (Vector2){START_BUTTON_POS.x, START_BUTTON_POS.y},   // origin
        (Vector2){START_BUTTON_SIZE.x, START_BUTTON_SIZE.y}, // original size
        (Vector2){START_BUTTON_SIZE.x, START_BUTTON_SIZE.y}, // current size
        0.0f,                                                // rot
        0.0f,                                                // rot speed
        DARKBLUE,                                            // color
        false,                                               // click
        false,                                               // hover
        false,                                               // hold
        {
            /* AnimatableText */
            (Vector2){START_BUTTON_POS.x, START_BUTTON_POS.y}, // originWARNING_CONTDOWN_POS
            "START",                                           // text
            ENDLESS_BUTTON_TEXT_SIZE,                          // originalFontSize
            ENDLESS_BUTTON_TEXT_SIZE,                          // currentFontSize
            BLACK,                                             // fontColor
            0.0f,                                              // rot
            0.0f                                               // rot speed
        }};

    AnimatableButton _endlessBtn = {
        (Vector2){0.0f, 0.0f},                                   // origin
        (Vector2){ENDLESS_BUTTON_SIZE.x, ENDLESS_BUTTON_SIZE.y}, // original size
        (Vector2){ENDLESS_BUTTON_SIZE.x, ENDLESS_BUTTON_SIZE.y}, // current size
        0.0f,                                                    // rot
        0.0f,                                                    // rot speed
        ORANGE,                                                  // color
        false,                                                   // click
        false,                                                   // hover
        false,                                                   // hold
        {
            /* AnimatableText */
            (Vector2){0.0f, 0.0f},    // origin
            "ENDLESS MODE",           // text
            ENDLESS_BUTTON_TEXT_SIZE, // originalFontSize
            ENDLESS_BUTTON_TEXT_SIZE, // currentFontSize
            BLACK,                    // fontColor
            0.0f,                     // rot
            0.0f                      // rot speed
        }};

    int x = LEVEL_BUTTON_STARTING_X;
    int y = LEVEL_BUTTON_STARTING_Y;

    for (int i = 0; i < TOTAL_LEVELS; i++)
    {
        Level level = Get_Level(i);
        Color color;
        if (level.locked)
        {
            color = LEVEL_BUTTON_LOCKED_COLOR;
        }
        else if (level.highscore == 0)
        {
            color = LEVEL_BUTTON_UNFINISHED_COLOR;
        }
        else
        {
            color = LEVEL_BUTTON_FINISHED_COLOR;
        }

        AnimatableButton _level_button = {
            (Vector2){x, y},                                     // origin
            (Vector2){LEVEL_BUTTON_SIZE.x, LEVEL_BUTTON_SIZE.y}, // original size
            (Vector2){LEVEL_BUTTON_SIZE.x, LEVEL_BUTTON_SIZE.y}, // current size
            0.0f,                                                // rot
            0.0f,                                                // rot speed
            color,                                               // color
            false,                                               // click
            false,                                               // hover
            false,                                               // hold
            {
                /* AnimatableText */
                (Vector2){x, y}, // origin
                "\0",            // text
                18.0f,           // originalFontSize
                18.0f,           // currentFontSize
                BLACK,           // fontColor
                0.0f,            // rot
                0.0f             // rot speed
            }};

        if (level.locked == false)
        {
            sprintf(_level_button.btnText.text, "%d", i + 1);
        }

        level_buttons[i] = _level_button;

        if (i != 0 && (i + 1) % LEVEL_COLS == 0)
        {
            y += LEVEL_BUTTON_SIZE.y + 5.0f;
            x = LEVEL_BUTTON_STARTING_X;
        }
        else
        {
            x += LEVEL_BUTTON_SIZE.x + 5.0f;
        }
    }

    _endlessBtn.origin = (Vector2){halfScreenW, y + (LEVEL_BUTTON_SIZE.y / 2.0f)};
    _endlessBtn.btnText.origin = _endlessBtn.origin;

    startBtn = _startBtn;
    endlessBtn = _endlessBtn;
    hasInitialized = true;
}

void Fetch_Level_Status()
{
    for (int i = 0; i < TOTAL_LEVELS; i++)
    {
        levelStatus[i] = Is_Level_Locked(i);
    }
}

bool Has_Level_Been_Selected()
{

    for (int i = 0; i < TOTAL_LEVELS; i++)
    {
        if (level_buttons[i].click && !Is_Level_Locked(i))
        {
            Load_Level(i);
            return true;
        }
    }

    return false;
}

void Load_Gameplay(GameScreen *current_game_screen)
{
    *current_game_screen = GAMEPLAY_SCREEN;
}

void Show_Start()
{
    CreateText("SHOOT DOWN!", TITLE_SIZE, RED, TITLE_POS.x, TITLE_POS.y, 0, 0);
    CreateButton_Rectangle(startBtn.btnText.text, startBtn.btnText.currentFontSize, startBtn.btnText.fontColor, startBtn.currentSize.x, startBtn.currentSize.y, startBtn.color, startBtn.origin.x, startBtn.origin.y, 0, 0, &startBtn.click, &startBtn.hover, &startBtn.hold);
    PulsateAnimation_Btn(&startBtn, startBtn.originalSize.x / 1.5f, startBtn.originalSize.y / 1.5f, startBtn.originalSize.x, startBtn.originalSize.y, startBtn.btnText.originalFontSize / 1.5f, startBtn.btnText.originalFontSize, 2.5f);

    if (startBtn.click)
    {
        showLevelSelect = true;
    }
}

void Show_LevelSelect()
{
    if (!hasFetchedLevelStatus)
    {
        Fetch_Level_Status();
    }

    CreateText("LEVEL SELECT", LEVELSELECT_TITLE_SIZE, RED, LEVELSELECT_TITLE_POS.x, LEVELSELECT_TITLE_POS.y, 0, 0);

    for (int i = 0; i < TOTAL_LEVELS; i++)
    {
        CreateButton_Rectangle(level_buttons[i].btnText.text, level_buttons[i].btnText.currentFontSize, level_buttons[i].btnText.fontColor, level_buttons[i].currentSize.x, level_buttons[i].currentSize.y, level_buttons[i].color, level_buttons[i].origin.x, level_buttons[i].origin.y, 0, 0, &level_buttons[i].click, &level_buttons[i].hover, &level_buttons[i].hold);

        if (level_buttons[i].btnText.text[0] == '\0')
        {
            CreateSprite_NoCollider(SPRITE_LOCKED, 16, 16, 0, level_buttons[i].origin.x, level_buttons[i].origin.y, WHITE, false);
        }
    }

    CreateButton_Rectangle(endlessBtn.btnText.text, endlessBtn.btnText.currentFontSize, endlessBtn.btnText.fontColor, endlessBtn.currentSize.x, endlessBtn.currentSize.y, endlessBtn.color, endlessBtn.origin.x, endlessBtn.origin.y, 0, 0, &endlessBtn.click, &endlessBtn.hover, &endlessBtn.hold);
}

void Display_MainMenu(GameScreen *current_game_screen)
{
    if (!hasInitialized)
    {
        InitializeVariables();
    }

    if (!showLevelSelect)
    {
        Show_Start();
    }
    else
    {
        if (!Has_Level_Been_Selected())
        {
            Show_LevelSelect();
        }
        else
        {
            Load_Gameplay(current_game_screen);
        }
    }
}