#pragma once

#include "../lib/raylib6/include/raylib.h"
#include "enums.h"

typedef struct
{
    Vector2 vertices[4];
} OBBCollider;

typedef struct
{
    bool active;
    Vector2 origin;
    float width;
    float height;
    float rotation;
    float rotationSpeed;

    OBBCollider collider;

    Vector2 gravityMultiplier;

    int points_for_destruction;
} PhysicsObject;

typedef struct
{
    Vector2 origin;
    char text[256];
    float originalFontSize;
    float currentFontSize;
    Color fontColor;
    float rotation;
    float rotationSpeed;
} AnimatableText;

typedef struct
{
    AnimatableText text_component;
    PhysicsObject physics_component;
} PhysicsObject_Text;

typedef struct
{
    Vector2 origin;
    Vector2 originalSize;
    Vector2 currentSize;

    float rotation;
    float rotationSpeed;

    Color color;

    bool click;
    bool hover;
    bool hold;

    AnimatableText btnText;
} AnimatableButton;

typedef struct
{
    bool locked;
    int minPoints;
    int highscore;
    int waves;                  // length of the array down here
    int *waves_starting_points; // array of ints, each int is the starting point of each wave in the PhysicsObjects array in gameplay.c
    int phys_objs_to_throw;

    Vector2 min_gravity_multiplier;
    Vector2 max_gravity_multiplier;
    Vector2 min_spawn_pos;
    Vector2 max_spawn_pos;

} Level;

typedef struct
{
    bool isDone;
    float max_lifetime; /* Passed this amount the timer is considered done. Be careful of whether you update the timer by ticking up or ticking down!*/
    float lifetime;
    bool second_passed; /* Turns to true when a second has passed and stays true until explicitly reset in timer.h */
} Timer;