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
#include "../headers/colliders.h"
#include "../headers/cutter.h"

#define PREPARE_TIME 5.0f

#define WARNING_ICON_POS ((Vector2){halfScreenW, halfScreenH - 100})
#define WARNING_ICON_SIZE ((Vector2){128, 128})
#define WARNING_TEXT1_POS ((Vector2){halfScreenW, (WARNING_ICON_POS.y + WARNING_ICON_SIZE.y / 2 + WARNING_TEXT1_SIZE)})
#define WARNING_TEXT1_SIZE 24
#define WARNING_TEXT2_POS ((Vector2){halfScreenW, WARNING_TEXT1_POS.y + WARNING_TEXT2_SIZE * 1.5f})
#define WARNING_TEXT2_SIZE 24
#define WARNING_COUNTDOWN_SIZE 64
#define WARNING_CONTDOWN_POS ((Vector2){halfScreenW, WARNING_TEXT2_POS.y + WARNING_COUNTDOWN_SIZE * 2.0f})

#define OBTAINED_POINTS_POS ((Vector2){screenW - MeasureText(obtained_points.text, obtained_points.currentFontSize) * 1.5f, 25.0f})
#define OBTAINED_POINTS_SIZE 22
#define OBTAINED_POINTS_COLOR WHITE
#define OBTAINED_POINTS_AMOUNT_POS ((Vector2){screenW - MeasureText(obtained_points.text, obtained_points.currentFontSize) / 1.5f, 25.0f})
#define OBTAINED_POINTS_AMOUNT_SIZE 20
#define OBTAINED_POINTS_AMOUNT_COLOR YELLOW

#define END_TEXT_REQUIRED_TEXT "POINTS REQUIRED: "
#define END_TEXT_REQUIRED_POS ((Vector2){halfScreenW - MeasureText(END_TEXT_REQUIRED_TEXT, END_TEXT_REQUIRED_SIZE) / 4, 200.0f})
#define END_TEXT_REQUIRED_SIZE 32
#define END_TEXT_REQUIRED_COLOR RED
#define END_TEXT_REQUIRED_AMOUNT_POS ((Vector2){halfScreenW + MeasureText(END_TEXT_REQUIRED_TEXT, END_TEXT_REQUIRED_SIZE) / 2, 200.0f})
#define END_TEXT_REQUIRED_AMOUNT_SIZE 28
#define END_TEXT_REQUIRED_AMOUNT_COLOR BLUE

#define END_TEXT_OBTAINED_TEXT "POINTS OBTAINED: "
#define END_TEXT_OBTAINED_POS ((Vector2){halfScreenW - MeasureText(END_TEXT_OBTAINED_TEXT, END_TEXT_OBTAINED_SIZE) / 4, END_TEXT_REQUIRED_POS.y + 100.0f})
#define END_TEXT_OBTAINED_SIZE 32
#define END_TEXT_OBTAINED_COLOR RED
#define END_TEXT_OBTAINED_AMOUNT_POS ((Vector2){halfScreenW + MeasureText(END_TEXT_OBTAINED_TEXT, END_TEXT_OBTAINED_SIZE) / 2, END_TEXT_REQUIRED_AMOUNT_POS.y + 100.0f})
#define END_TEXT_OBTAINED_AMOUNT_SIZE 28
#define END_TEXT_OBTAINED_AMOUNT_COLOR YELLOW

typedef enum Gameplay_screen_info
{
    GAMEPLAY_WARNING,
    GAMEPLAY_GAME,
    GAMEPLAY_END
} Gameplay_screen_info;

bool has_initialized_level;
Level level;

Gameplay_screen_info screen_info;

AnimatableText warning_time_txt;
Timer timer;

AnimatableText obtained_points;

PhysicsObject *objs;
int obj_length;
int last_occupied_slot;

int current_wave;
int current_score;

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

    AnimatableText _obtained_points = {
        OBTAINED_POINTS_POS,
        "POINTS: ",
        OBTAINED_POINTS_SIZE,
        OBTAINED_POINTS_SIZE,
        OBTAINED_POINTS_COLOR,
        0.0f,
        0.0f,
    };

    obtained_points = _obtained_points;

    obj_length = level.phys_objs_to_throw + (level.phys_objs_to_throw * 4);

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

    last_occupied_slot = level.phys_objs_to_throw - 1;

    Activate_Wave(objs, level.phys_objs_to_throw, 0);

    has_initialized_level = true;

    screen_info = GAMEPLAY_GAME;
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
        screen_info = GAMEPLAY_GAME;
    }
}

void MouseInput(PhysicsObject **objs)
{

    Vector2 mousePos = GetMousePosition();

    int collision_index = -1;
    for (int i = 0; i <= last_occupied_slot; i++)
    {
        if (CheckMouseOverlap_Single(mousePos, (*objs)[i])) // objs[i] but pointing to the actual element
        {
            collision_index = i;
            break;
        }
    }

    if (collision_index == -1)
    {
        return;
    }

    /* Is there space for new objects? */
    if (last_occupied_slot < obj_length - 5)
    {
        CutTo4Pieces((*objs)[collision_index], mousePos, *objs, last_occupied_slot + 1, true);
        last_occupied_slot += 4;
    }

    if ((*objs)[collision_index].width == CRATE_WIDTH)
    {
        current_score += POINTS_FOR_CRATES_DESTRUCTION;
    }
    else
    {
        current_score += POINTS_FOR_DEBRIS_DESTRUCTION;
    }

    (*objs)[collision_index].active = false;
    (*objs)[collision_index].origin = (Vector2){9999.0f, 9999.0f};
}

void UpdateCrates()
{

    // Check Collision
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        MouseInput(&objs);
    }

    int amount_of_inactive_objs = 0;

    for (int i = level.waves_starting_points[current_wave]; i < obj_length; i++)
    {
        if (!objs[i].active)
        {
            amount_of_inactive_objs++;
            continue;
        }

        objs[i].origin = ApplyGravity(objs[i].origin, &objs[i].gravityMultiplier);
        objs[i].rotation = ApplyRotation(objs[i].rotation, objs[i].rotationSpeed);

        if (objs[i].width == CRATE_WIDTH)
        {
            CreateSprite_NoCollider(SPRITE_BOX, objs[i].width, objs[i].height, objs[i].rotation, objs[i].origin.x, objs[i].origin.y, WHITE, false);
        }
        else
        {
            CreateSprite_NoCollider(SPRITE_BOX_PIECE, objs[i].width, objs[i].height, objs[i].rotation, objs[i].origin.x, objs[i].origin.y, WHITE, false);
        }

        if (objs[i].origin.y > screenH + objs[i].width || objs[i].origin.x > screenW + objs[i].width)
        {
            objs[i].active = false;
        }
    }

    UpdateColliders(objs, obj_length);

    int end = obj_length - level.waves_starting_points[current_wave];

    if (amount_of_inactive_objs >= end)
    {
        printf("\nyes\n");
        if (current_wave == level.waves - 1)
        {
            screen_info = GAMEPLAY_END;
            return;
        }
        else
        {
            Activate_Wave(objs, obj_length, current_wave + 1);
        }
    }

    CreateText(obtained_points.text, obtained_points.currentFontSize, obtained_points.fontColor, OBTAINED_POINTS_POS.x, OBTAINED_POINTS_POS.y, 0, 0);
    CreateTextFromInt(current_score, OBTAINED_POINTS_AMOUNT_SIZE, OBTAINED_POINTS_AMOUNT_COLOR, OBTAINED_POINTS_AMOUNT_POS.x, OBTAINED_POINTS_AMOUNT_POS.y, 0, 0);

    // CreateTextFromInt(GetFPS(), 24, RED, halfScreenW, 100, 0, 0);
}

void ShowEnd()
{
    CreateText(END_TEXT_REQUIRED_TEXT, END_TEXT_REQUIRED_SIZE, END_TEXT_REQUIRED_COLOR, END_TEXT_REQUIRED_POS.x, END_TEXT_REQUIRED_POS.y, 0, 0);
    CreateTextFromInt(level.minPoints, END_TEXT_REQUIRED_AMOUNT_SIZE, END_TEXT_REQUIRED_AMOUNT_COLOR, END_TEXT_REQUIRED_AMOUNT_POS.x, END_TEXT_REQUIRED_AMOUNT_POS.y, 0, 0);

    CreateText(END_TEXT_OBTAINED_TEXT, END_TEXT_OBTAINED_SIZE, END_TEXT_OBTAINED_COLOR, END_TEXT_OBTAINED_POS.x, END_TEXT_OBTAINED_POS.y, 0, 0);
    CreateTextFromInt(current_score, END_TEXT_OBTAINED_AMOUNT_SIZE, END_TEXT_OBTAINED_AMOUNT_COLOR, END_TEXT_OBTAINED_AMOUNT_POS.x, END_TEXT_OBTAINED_AMOUNT_POS.y, 0, 0);
}

void Display_Gameplay_Screen()
{

    if (!has_initialized_level)
    {
        Initialize_Level();
    }

    switch (screen_info)
    {
    case GAMEPLAY_WARNING:
        ShowWarning();
        UpdateTimer_Tickdown(&timer);
        break;
    case GAMEPLAY_GAME:
        UpdateCrates();
        break;
    case GAMEPLAY_END:
        ShowEnd();
    }
}