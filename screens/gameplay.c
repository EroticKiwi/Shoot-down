#include "gameplay.h"
#include "../headers/levels.h"
#include "../utils/structs.h"
#include "../headers/sprites.h"
#include "../headers/screen.h"
#include "../headers/timer.h"
#include "../headers/animations.h"
#include "../headers/sound.h"
#include "../headers/memory_management.h"
#include "../headers/misc.h"
#include "../headers/physics.h"

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

PhysicsObject *objs;
int obj_length;

int current_wave;

void Activate_Wave(PhysicsObject *objs, int obj_length, int wave_to_activate)
{

    if (wave_to_activate >= level.waves)
    {
        return;
    }

    int start = level.waves_starting_points[wave_to_activate];
    int stop;

    if (wave_to_activate == level.waves - 1)
    {
        stop = obj_length;
    }
    else
    {
        stop = level.waves_starting_points[wave_to_activate + 1];
    }

    for (int i = start; i < stop; i++)
    {
        objs[i].active = true;
    }

    current_wave = wave_to_activate;
}

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

    obj_length = level.phys_objs_to_throw * 4;

    // 1. Expand
    objs = Memory_Create(objs, obj_length, sizeof(PhysicsObject));

    Vector2 origin;
    Vector2 gravity_multiplier;
    bool isActive;

    // 2. Cycle and assign
    for (int i = 0; i < level.phys_objs_to_throw; i++)
    {
        origin = (Vector2){RandomNumberInRange_Inclusive(level.min_spawn_pos.x, level.max_spawn_pos.x), RandomNumberInRange_Inclusive(level.min_spawn_pos.y, level.max_spawn_pos.y)};
        gravity_multiplier = (Vector2){RandomNumberInRange_Inclusive(level.min_gravity_multiplier.x, level.max_gravity_multiplier.x), RandomNumberInRange_Inclusive(level.min_gravity_multiplier.y, level.max_gravity_multiplier.y)};

        InitializePhysicsObject(&objs[i], origin, CRATE_WIDTH, CRATE_HEIGHT, 0.0f, RandomNumberInRange_Inclusive(MIN_ROTATION, MAX_ROTATION), gravity_multiplier, false);
    }

    Activate_Wave(objs, level.phys_objs_to_throw, 0);

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
    int amount_of_inactive_objs = 0;

    int start = level.waves_starting_points[current_wave];
    int stop;

    if(current_wave + 1 >= level.waves){
        stop = level.phys_objs_to_throw;
    } else {
        stop = level.waves_starting_points[current_wave+1];
    }

    for (int i = start; i < stop; i++) // optimize here by starting from correct wave_starting_point!
    {
        if (!objs[i].active)
        {
            amount_of_inactive_objs++;
            continue;
        }

        objs[i].origin = ApplyGravity(objs[i].origin, &objs[i].gravityMultiplier);
        objs[i].rotation = ApplyRotation(objs[i].rotation, objs[i].rotationSpeed);

        CreateSprite_NoCollider(SPRITE_BOX, objs[i].width, objs[i].height, objs[i].rotation, objs[i].origin.x, objs[i].origin.y, WHITE, false);
        if (objs[i].origin.y > screenH + objs[i].width || objs[i].origin.x > screenW + objs[i].width)
        {
            objs[i].active = false;
        }
    }

    if (current_wave == level.waves - 1)
    {
        if (amount_of_inactive_objs == level.phys_objs_to_throw - level.waves_starting_points[current_wave])
        {
            printf("\nEND!\n");
        }
    }

    if (amount_of_inactive_objs == level.waves_starting_points[current_wave + 1])
    {
        Activate_Wave(objs, obj_length, current_wave + 1);
    }

    // CreateTextFromInt(GetFPS(), 24, RED, halfScreenW, 100, 0, 0);
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