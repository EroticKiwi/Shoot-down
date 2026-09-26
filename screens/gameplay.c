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

#define END_TEXT_LEVEL_PASSED_TEXT "LEVEL PASSED!"
#define END_TEXT_LEVEL_PASSED_TEXT_COLOR YELLOW
#define END_TEXT_LEVEL_NOT_PASSED_TEXT "LEVEL NOT PASSED!"
#define END_TEXT_LEVEL_NOT_PASSED_TEXT_COLOR RED
#define END_TEXT_LEVEL_SIZE 24
#define END_TEXT_LEVEL_POS ((Vector2){halfScreenW, 100.0f})

#define END_TEXT_REQUIRED_TEXT "POINTS REQUIRED: "
#define END_TEXT_REQUIRED_POS ((Vector2){halfScreenW - MeasureText(END_TEXT_REQUIRED_TEXT, END_TEXT_REQUIRED_SIZE) / 4, 200.0f})
#define END_TEXT_REQUIRED_SIZE 32
#define END_TEXT_REQUIRED_COLOR RED
#define END_TEXT_REQUIRED_AMOUNT_POS ((Vector2){halfScreenW + MeasureText(END_TEXT_REQUIRED_TEXT, END_TEXT_REQUIRED_SIZE) / 2, 200.0f})
#define END_TEXT_REQUIRED_AMOUNT_SIZE 28
#define END_TEXT_REQUIRED_AMOUNT_COLOR WHITE

#define END_TEXT_OBTAINED_TEXT "POINTS OBTAINED: "
#define END_TEXT_OBTAINED_POS ((Vector2){halfScreenW - MeasureText(END_TEXT_OBTAINED_TEXT, END_TEXT_OBTAINED_SIZE) / 4, END_TEXT_REQUIRED_POS.y + 100.0f})
#define END_TEXT_OBTAINED_SIZE 32
#define END_TEXT_OBTAINED_COLOR RED
#define END_TEXT_OBTAINED_AMOUNT_POS ((Vector2){halfScreenW + MeasureText(END_TEXT_OBTAINED_TEXT, END_TEXT_OBTAINED_SIZE) / 2, END_TEXT_REQUIRED_AMOUNT_POS.y + 100.0f})
#define END_TEXT_OBTAINED_AMOUNT_SIZE 28
#define END_TEXT_OBTAINED_AMOUNT_COLOR YELLOW

#define END_TEXT_HIGHSCORE_TEXT "HIGHSCORE: "
#define END_TEXT_HIGHSCORE_POS ((Vector2){halfScreenW - MeasureText(END_TEXT_HIGHSCORE_TEXT, END_TEXT_HIGHSCORE_SIZE) / 4, END_TEXT_OBTAINED_POS.y + 100.0f})
#define END_TEXT_HIGHSCORE_SIZE 32
#define END_TEXT_HIGHSCORE_COLOR RED
#define END_TEXT_HIGHSCORE_AMOUNT_POS ((Vector2){halfScreenW + MeasureText(END_TEXT_HIGHSCORE_TEXT, END_TEXT_HIGHSCORE_SIZE) / 2, END_TEXT_OBTAINED_AMOUNT_POS.y + 100.0f})
#define END_TEXT_HIGHSCORE_AMOUNT_SIZE 28
#define END_TEXT_HIGHSCORE_AMOUNT_COLOR BLUE

#define END_TEXT_NEW_HIGHSCORE_TEXT "NEW HIGHSCORE!"
#define END_TEXT_NEW_HIGHSCORE_TEXT_SIZE 16
#define END_TEXT_NEW_HIGHSCORE_TEXT_COLOR YELLOW
#define END_TEXT_NEW_HIGHSCORE_POS ((Vector2){END_TEXT_HIGHSCORE_POS.x, END_TEXT_HIGHSCORE_POS.y + END_TEXT_NEW_HIGHSCORE_TEXT_SIZE * 2})

#define END_BUTTON_NEXT_LEVEL_TEXT "NEXT LEVEL"
#define END_BUTTON_NEXT_LEVEL_TEXT_COLOR BLACK
#define END_BUTTON_NEXT_LEVEL_TEXT_SIZE 18
#define END_BUTTON_NEXT_LEVEL_POS ((Vector2){END_TEXT_HIGHSCORE_POS.x, END_TEXT_HIGHSCORE_POS.y + 100.0f})
#define END_BUTTON_NEXT_LEVEL_SIZE ((Vector2){END_BUTTON_NEXT_LEVEL_TEXT_SIZE + 120.0f, END_BUTTON_NEXT_LEVEL_TEXT_SIZE + 50.0f})
#define END_BUTTON_NEXT_LEVEL_COLOR ORANGE

#define END_BUTTON_TRY_AGAIN_TEXT "TRY AGAIN"
#define END_BUTTON_TRY_AGAIN_TEXT_COLOR BLACK
#define END_BUTTON_TRY_AGAIN_TEXT_SIZE 18
#define END_BUTTON_TRY_AGAIN_POS ((Vector2){END_BUTTON_NEXT_LEVEL_POS.x, END_BUTTON_NEXT_LEVEL_POS.y + END_BUTTON_NEXT_LEVEL_SIZE.y + 15.0f})
#define END_BUTTON_TRY_AGAIN_SIZE ((Vector2){END_BUTTON_TRY_AGAIN_TEXT_SIZE + 120.0f, END_BUTTON_TRY_AGAIN_TEXT_SIZE + 50.0f})
#define END_BUTTON_TRY_AGAIN_COLOR BLUE

#define END_BUTTON_LEVEL_SELECT_TEXT "LEVEL SELECT"
#define END_BUTTON_LEVEL_SELECT_TEXT_COLOR BLACK
#define END_BUTTON_LEVEL_SELECT_TEXT_SIZE 18
#define END_BUTTON_LEVEL_SELECT_POS ((Vector2){END_BUTTON_TRY_AGAIN_POS.x, END_BUTTON_TRY_AGAIN_POS.y + END_BUTTON_TRY_AGAIN_SIZE.y + 15.0f})
#define END_BUTTON_LEVEL_SELECT_SIZE ((Vector2){END_BUTTON_LEVEL_SELECT_TEXT_SIZE + 120.0f, END_BUTTON_LEVEL_SELECT_TEXT_SIZE + 50.0f})
#define END_BUTTON_LEVEL_SELECT_COLOR RED

#define SCORE_TEXT_SIZE 18
#define SCORE_TEXT_COLOR YELLOW

#define COUNT_ANIMATION_TIME 0.01f
#define END_WAIT_TIME 1.0f

typedef enum Gameplay_screen_info
{
    GAMEPLAY_WARNING,
    GAMEPLAY_GAME,
    GAMEPLAY_END
} Gameplay_screen_info;

bool has_initialized_level;
Level level;

/* Tells us what to display in the gameplay screen */
Gameplay_screen_info screen_info;

AnimatableText warning_time_txt;
Timer timer;
AnimatableText obtained_points;

/* Score Text (text that shows when destroying a crate)*/
PhysicsObject_Text *score_text;
int score_text_length;
int last_active_score_text = -1;

/* Crates physics objects */
PhysicsObject *objs;
int obj_length;
int last_occupied_slot;

/* stats */
int current_wave;
int current_score;
int score_count_animation;
int highscore_count_animation;

/* bools */
bool end_text_0_appeared;
bool end_text_1_appeared;
bool end_text_2_appeared;
bool end_text_3_appeared;
bool end_text_3_completed;
bool end_buttons_appeared;
bool new_highscore;

/* end buttons */
bool nextlevel_trigger;
bool tryagain_trigger;
bool levelselect_trigger;

/*
    TWO ARRAYS OF STRUCT IN HEAP:
        - OBJS (PhysicsObjects)
        - SCORE_TEXT (PhysicsObjects_Text)
*/

void Reset_Gameplay()
{
    /* bools */
    end_text_1_appeared = false;
    end_text_2_appeared = false;
    end_text_3_appeared = false;
    end_text_3_completed = false;
    end_buttons_appeared = false;
    new_highscore = false;
    screen_info = GAMEPLAY_WARNING;

    has_initialized_level = false;
}

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
        false,               // isDone
        0.0f,                // max_lifetime
        PREPARE_TIME + 1.0f, // lifetime
        false                // second_passed
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

    obj_length = level.phys_objs_to_throw + (level.phys_objs_to_throw * 8); // it's a lot of space, I know

    // 1. Expand
    objs = Memory_Resize(objs, obj_length, sizeof(PhysicsObject)); // acts as memory_create as well!

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

    score_text = Memory_Resize(score_text, level.phys_objs_to_throw * 1.5f, sizeof(PhysicsObject_Text)); // acts as memory_create as well!

    score_text_length = level.phys_objs_to_throw * 1.5f;

    for (int i = 0; i < score_text_length; i++)
    {
        score_text[i].physics_component.active = false;
        score_text[i].physics_component.width = 0.0f;
        score_text[i].physics_component.height = 0.0f;
        score_text[i].physics_component.gravityMultiplier = (Vector2){0.0f, 0.0f};
        score_text[i].physics_component.origin = (Vector2){9999.0f, 9999.0f};

        score_text[i].text_component.text[0] = '\0';
        score_text[i].text_component.fontColor = SCORE_TEXT_COLOR;
        score_text[i].text_component.originalFontSize = SCORE_TEXT_SIZE;
        score_text[i].text_component.currentFontSize = SCORE_TEXT_SIZE;
        score_text[i].text_component.rotation = 0.0f;
        score_text[i].text_component.rotationSpeed = 0.0f;
        score_text[i].text_component.origin = (Vector2){9999.0f, 9999.0f};
    }

    has_initialized_level = true;

    current_score = 0;
}

void EndLevel()
{
    screen_info = GAMEPLAY_END;
    Set_Timer(&timer, 1.0f, 0.0f);

    Set_Highscore(current_score);
    if (current_score >= level.minPoints)
    {
        Save_Levels_Data();
    }
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

void Create_Score_Text(Vector2 origin, bool destroyed_crate)
{

    int start = last_active_score_text;

    if (start == score_text_length - 1 || start == -1)
    {
        start = 0;
    }

    int points;
    if (destroyed_crate)
    {
        points = POINTS_FOR_CRATES_DESTRUCTION;
    }
    else
    {
        points = POINTS_FOR_DEBRIS_DESTRUCTION;
    }

    for (int i = start; i < score_text_length; i++)
    {
        if (score_text[i].physics_component.active == false)
        {
            sprintf(score_text[i].text_component.text, "+%d", points);
            score_text[i].text_component.fontColor = SCORE_TEXT_COLOR;

            score_text[i].physics_component.origin = origin;
            score_text[i].physics_component.gravityMultiplier = (Vector2){0.0f, 300.0f};
            score_text[i].physics_component.active = true;

            last_active_score_text = i;
            return;
        }
    }

    sprintf(score_text[0].text_component.text, "+%d", points);
    score_text[0].text_component.fontColor = SCORE_TEXT_COLOR;

    score_text[0].physics_component.origin = origin;
    score_text[0].physics_component.gravityMultiplier = (Vector2){0.0f, 300.0f};
    score_text[0].physics_component.active = true;

    last_active_score_text = 0;
}

void Update_Score_Text()
{

    int alpha = 255.0f;

    for (int i = 0; i < score_text_length; i++)
    {

        if (score_text[i].physics_component.active == false)
        {
            continue;
        }

        score_text[i].physics_component.origin = ApplyGravity(score_text[i].physics_component.origin, &score_text[i].physics_component.gravityMultiplier);
        alpha = Tweening((float)score_text[i].text_component.fontColor.a, 0.0f, 200.0f);
        score_text[i].text_component.fontColor.a = alpha;
        if (score_text[i].text_component.fontColor.a <= 0.0f)
        {
            score_text[i].physics_component.active = false;
        }

        CreateText(score_text[i].text_component.text, score_text[i].text_component.currentFontSize, score_text[i].text_component.fontColor, score_text[i].physics_component.origin.x, score_text[i].physics_component.origin.y, 0, 0);
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
        Create_Score_Text(mousePos, true);
    }
    else
    {
        current_score += POINTS_FOR_DEBRIS_DESTRUCTION;
        Create_Score_Text(mousePos, false);
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

    /* Physics and Drawing of the crates */

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

        if (objs[i].origin.y > screenH + objs[i].width || objs[i].origin.y < -objs[i].height || objs[i].origin.x > screenW + objs[i].width || objs[i].origin.x < -objs[i].width)
        {
            objs[i].active = false;
        }
    }

    UpdateColliders(objs, obj_length);

    Update_Score_Text();

    /* Check end of wave */
    int end = obj_length - level.waves_starting_points[current_wave];
    if (amount_of_inactive_objs >= end)
    {
        // printf("\nend of wave!\n");
        if (current_wave == level.waves - 1)
        {
            EndLevel();
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

void ShowEnd(GameScreen *current_game_screen)
{

    if (!end_text_0_appeared)
    {
        UpdateTimer_Tickdown(&timer);
        if (Is_Timer_Done(&timer))
        {
            end_text_0_appeared = true;
            Set_Timer(&timer, END_WAIT_TIME, 0.0f);
        }
        return;
    }

    if (current_score >= level.minPoints)
    {
        CreateText(END_TEXT_LEVEL_PASSED_TEXT, END_TEXT_LEVEL_SIZE, END_TEXT_LEVEL_PASSED_TEXT_COLOR, END_TEXT_LEVEL_POS.x, END_TEXT_LEVEL_POS.y, 0, 0);
    }
    else
    {
        CreateText(END_TEXT_LEVEL_NOT_PASSED_TEXT, END_TEXT_LEVEL_SIZE, END_TEXT_LEVEL_NOT_PASSED_TEXT_COLOR, END_TEXT_LEVEL_POS.x, END_TEXT_LEVEL_POS.y, 0, 0);
    }

    if (!end_text_1_appeared)
    {
        UpdateTimer_Tickdown(&timer);
        if (Is_Timer_Done(&timer))
        {
            end_text_1_appeared = true;
            Set_Timer(&timer, END_WAIT_TIME, 0.0f);
        }
        return;
    }

    CreateText(END_TEXT_REQUIRED_TEXT, END_TEXT_REQUIRED_SIZE, END_TEXT_REQUIRED_COLOR, END_TEXT_REQUIRED_POS.x, END_TEXT_REQUIRED_POS.y, 0, 0);
    CreateTextFromInt(level.minPoints, END_TEXT_REQUIRED_AMOUNT_SIZE, END_TEXT_REQUIRED_AMOUNT_COLOR, END_TEXT_REQUIRED_AMOUNT_POS.x, END_TEXT_REQUIRED_AMOUNT_POS.y, 0, 0);

    if (!end_text_2_appeared)
    {
        UpdateTimer_Tickdown(&timer);
        if (Is_Timer_Done(&timer))
        {
            end_text_2_appeared = true;
            Set_Timer(&timer, END_WAIT_TIME, 0.0f);
            score_count_animation = 0;
        }
        return;
    }

    CreateText(END_TEXT_OBTAINED_TEXT, END_TEXT_OBTAINED_SIZE, END_TEXT_OBTAINED_COLOR, END_TEXT_OBTAINED_POS.x, END_TEXT_OBTAINED_POS.y, 0, 0);
    CreateTextFromInt(score_count_animation, END_TEXT_OBTAINED_AMOUNT_SIZE, END_TEXT_OBTAINED_AMOUNT_COLOR, END_TEXT_OBTAINED_AMOUNT_POS.x, END_TEXT_OBTAINED_AMOUNT_POS.y, 0, 0);

    UpdateTimer_Tickdown(&timer);

    if (score_count_animation < current_score)
    {
        if (!Is_Timer_Done(&timer))
        {
            return;
        }
        score_count_animation += 2;
        if (score_count_animation >= current_score)
        {
            score_count_animation = current_score;
            highscore_count_animation = 0;
            Set_Timer(&timer, END_WAIT_TIME, 0.0f);
        }
        else
        {
            Set_Timer(&timer, COUNT_ANIMATION_TIME, 0.0f);
        }
        return;
    }

    CreateText(END_TEXT_HIGHSCORE_TEXT, END_TEXT_HIGHSCORE_SIZE, END_TEXT_HIGHSCORE_COLOR, END_TEXT_HIGHSCORE_POS.x, END_TEXT_HIGHSCORE_POS.y, 0, 0);
    CreateTextFromInt(highscore_count_animation, END_TEXT_HIGHSCORE_AMOUNT_SIZE, END_TEXT_HIGHSCORE_AMOUNT_COLOR, END_TEXT_HIGHSCORE_AMOUNT_POS.x, END_TEXT_HIGHSCORE_AMOUNT_POS.y, 0, 0);

    UpdateTimer_Tickdown(&timer);

    if (!end_text_3_completed)
    {
        if (!Is_Timer_Done(&timer))
        {
            return;
        }
        if (current_score >= level.highscore)
        {
            if (highscore_count_animation < current_score)
            {
                highscore_count_animation += 2;
                if (highscore_count_animation >= current_score)
                {
                    highscore_count_animation = current_score;
                    if (current_score > level.highscore)
                    {
                        new_highscore = true;
                    }
                    Set_Timer(&timer, END_WAIT_TIME, 0.0f);
                    end_text_3_completed = true;
                }
                else
                {
                    Set_Timer(&timer, COUNT_ANIMATION_TIME, 0.0f);
                }
                return;
            }
        }
        else
        {
            if (highscore_count_animation < level.highscore)
            {
                highscore_count_animation += 2;
                if (highscore_count_animation >= level.highscore)
                {
                    highscore_count_animation = level.highscore;
                    Set_Timer(&timer, END_WAIT_TIME, 0.0f);
                    end_text_3_completed = true;
                }
                else
                {
                    Set_Timer(&timer, COUNT_ANIMATION_TIME, 0.0f);
                }
                return;
            }
        }
    }

    if (new_highscore)
    {
        CreateText(END_TEXT_NEW_HIGHSCORE_TEXT, END_TEXT_NEW_HIGHSCORE_TEXT_SIZE, END_TEXT_NEW_HIGHSCORE_TEXT_COLOR, END_TEXT_NEW_HIGHSCORE_POS.x, END_TEXT_NEW_HIGHSCORE_POS.y, 0, 0);
    }

    if (!end_buttons_appeared)
    {
        UpdateTimer_Tickdown(&timer);
        if (Is_Timer_Done(&timer))
        {
            end_buttons_appeared = true;
        }
        return;
    }

    if (current_score < level.minPoints)
    {
        CreateButton_Rectangle(END_BUTTON_NEXT_LEVEL_TEXT, END_BUTTON_NEXT_LEVEL_TEXT_SIZE, END_BUTTON_NEXT_LEVEL_TEXT_COLOR, END_BUTTON_NEXT_LEVEL_SIZE.x, END_BUTTON_NEXT_LEVEL_SIZE.y, GRAY, END_BUTTON_NEXT_LEVEL_POS.x, END_BUTTON_NEXT_LEVEL_POS.y, 0, 0, NULL, NULL, NULL);
    }
    else
    {
        if (Is_There_A_Next_Level())
        {
            CreateButton_Rectangle(END_BUTTON_NEXT_LEVEL_TEXT, END_BUTTON_NEXT_LEVEL_TEXT_SIZE, END_BUTTON_NEXT_LEVEL_TEXT_COLOR, END_BUTTON_NEXT_LEVEL_SIZE.x, END_BUTTON_NEXT_LEVEL_SIZE.y, END_BUTTON_NEXT_LEVEL_COLOR, END_BUTTON_NEXT_LEVEL_POS.x, END_BUTTON_NEXT_LEVEL_POS.y, 0, 0, &nextlevel_trigger, NULL, NULL);
        } else {
        CreateText("YOU FINISHED THE GAME!", 24, GREEN, END_BUTTON_NEXT_LEVEL_POS.x, END_BUTTON_NEXT_LEVEL_POS.y, 0, 0);
        }
    }

    CreateButton_Rectangle(END_BUTTON_TRY_AGAIN_TEXT, END_BUTTON_TRY_AGAIN_TEXT_SIZE, END_BUTTON_TRY_AGAIN_TEXT_COLOR, END_BUTTON_TRY_AGAIN_SIZE.x, END_BUTTON_TRY_AGAIN_SIZE.y, END_BUTTON_TRY_AGAIN_COLOR, END_BUTTON_TRY_AGAIN_POS.x, END_BUTTON_TRY_AGAIN_POS.y, 0, 0, &tryagain_trigger, NULL, NULL);
    CreateButton_Rectangle(END_BUTTON_LEVEL_SELECT_TEXT, END_BUTTON_LEVEL_SELECT_TEXT_SIZE, END_BUTTON_LEVEL_SELECT_TEXT_COLOR, END_BUTTON_LEVEL_SELECT_SIZE.x, END_BUTTON_LEVEL_SELECT_SIZE.y, END_BUTTON_LEVEL_SELECT_COLOR, END_BUTTON_LEVEL_SELECT_POS.x, END_BUTTON_LEVEL_SELECT_POS.y, 0, 0, &levelselect_trigger, NULL, NULL);

    if (levelselect_trigger)
    {
        *current_game_screen = MAIN_MENU_SCREEN;
        Reset_Gameplay();
        return;
    } else if(tryagain_trigger){
        Reset_Gameplay();
        return;
    } else if(nextlevel_trigger){
        Reset_Gameplay();
        Load_Level(Get_Loaded_Level_Index()+1);
        return;
    }
}

void Display_Gameplay_Screen(GameScreen *current_game_screen)
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
        ShowEnd(current_game_screen);
    }
}