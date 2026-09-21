#include "gameplay.h"
#include "../headers/levels.h"
#include "../utils/structs.h"
#include "../headers/sprites.h"
#include "../headers/screen.h"
#include "../headers/timer.h"
#include "../headers/animations.h"
#include "../headers/sound.h"

#define PREPARE_TIME 5.0f

#define WARNING_ICON_POS ((Vector2){halfScreenW, halfScreenH - 100})
#define WARNING_ICON_SIZE ((Vector2){128, 128})
#define WARNING_TEXT1_POS ((Vector2){halfScreenW, (WARNING_ICON_POS.y + WARNING_ICON_SIZE.y / 2 + WARNING_TEXT1_SIZE)})
#define WARNING_TEXT1_SIZE 24
#define WARNING_TEXT2_POS ((Vector2){halfScreenW, WARNING_TEXT1_POS.y + WARNING_TEXT2_SIZE * 1.5f})
#define WARNING_TEXT2_SIZE 24
#define WARNING_COUNTDOWN_SIZE 64
#define WARNING_CONTDOWN_POS ((Vector2){halfScreenW, WARNING_TEXT2_POS.y + WARNING_COUNTDOWN_SIZE * 2.0f})

bool has_initialized_level;
Level level;

bool ready_to_play = false;

AnimatableText warning_time_txt;
Timer timer;

void Initialize_Level()
{
    level = Get_Loaded_Level();

    Timer _timer = {
        false,              // isDone
        0.0f,               // max_lifetime
        PREPARE_TIME + 1.0f // lifetime
    };

    AnimatableText _warning_time_txt = {
        WARNING_CONTDOWN_POS,
        "", // will be handled by the associated timer
        WARNING_COUNTDOWN_SIZE,
        WARNING_COUNTDOWN_SIZE,
        RED,
        WARNING_CONTDOWN_POS.x,
        WARNING_CONTDOWN_POS.y};

    timer = _timer;
    warning_time_txt = _warning_time_txt;

    has_initialized_level = true;
}

void ShowWarning()
{
    CreateSprite_NoCollider(SPRITE_WARNING, WARNING_ICON_SIZE.x, WARNING_ICON_SIZE.y, 0, WARNING_ICON_POS.x, WARNING_ICON_POS.y, RED, false);
    CreateText("CRATES WILL FLY ON THE SCREEN", WARNING_TEXT1_SIZE, WHITE, WARNING_TEXT1_POS.x, WARNING_TEXT1_POS.y, 0, 0);
    CreateText("DESTROY AS MANY AS YOU CAN TO PASS THE LEVEL", WARNING_TEXT2_SIZE, WHITE, WARNING_TEXT2_POS.x, WARNING_TEXT2_POS.y, 0, 0);

    CreateTextFromInt(timer.lifetime, warning_time_txt.currentFontSize, warning_time_txt.fontColor, warning_time_txt.origin.x, warning_time_txt.origin.y, 0, 0);
    ChangeSize_OverTime(&warning_time_txt, warning_time_txt.originalFontSize / 2.0f, 25.0f);
    if (timer.second_passed)
    {
        warning_time_txt.currentFontSize = warning_time_txt.originalFontSize;
        Reset_seconds_passed(&timer);
        CreateSound(SOUND_BEEP);
    }

    if (timer.isDone)
    {
        ready_to_play = true;
    }
}

void UpdateCrates()
{
}

void Display_Gameplay_Screen()
{

    if (!has_initialized_level)
    {
        Initialize_Level();
    }

    if (!ready_to_play)
    {
        ShowWarning();
        UpdateTimer_Tickdown(&timer);
    }
    else
    {
        UpdateCrates();
    }
}