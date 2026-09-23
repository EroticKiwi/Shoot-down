#include "../headers/colliders.h"
#include <math.h>

typedef struct
{
    float min;
    float max;
} Projection;

float DotProduct(Vector2 vectorA, Vector2 vectorB)
{
    return (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y);
}

/* Returns the axis that connects two points in the space. (For example, point A is on the right of point B on a straight line, we get {1, 0})*/
Vector2 GetAxis(Vector2 vectorA, Vector2 vectorB)
{
    Vector2 axis;

    axis.x = vectorB.x - vectorA.x;
    axis.y = vectorB.y - vectorA.y;

    float length = sqrtf((axis.x * axis.x) + (axis.y * axis.y));

    if (length != 0)
    {
        axis.x = axis.x / length;

        axis.y = axis.y / length;
    }

    return axis;
}

/* Returns the projection of our collider on the given axis. */
/* In simple words it takes our collider and it puts it on the axis, then we search for the interval in the space that it occupies. */
/* At the end of this function we will have the min point and the max point, and everything in between these two points is gonna be space occupied by our collider on that specific axis. */
Projection GetProjection(OBBCollider coll, Vector2 axis)
{
    Projection finalProjection;

    finalProjection.min = DotProduct(axis, coll.vertices[0]);
    finalProjection.max = finalProjection.min;

    for (int i = 0; i < 4; i++)
    {
        float projection = DotProduct(axis, coll.vertices[i]); // Where on the projection line does our vertex[i] fall?

        if (projection < finalProjection.min) /* Is it less than the min point? */
        {

            finalProjection.min = projection;
        }

        if (projection > finalProjection.max) /* Is it more than the max point? */
        {

            finalProjection.max = projection;
        }
    }

    /* What we have in the end is basically an interval that goes from the min to the max and our collider occupies exactly
    the space in between those two points. */

    return finalProjection;
}

void CalculateVertices(PhysicsObject *obj)
{
    float rotation = obj->rotation * DEG2RAD;
    float vertex_sin = sinf(rotation);
    float vertex_cos = cosf(rotation);

    obj->collider.vertices[0].x = obj->origin.x + ((-obj->width / 2) * vertex_cos - ((-obj->height / 2) * vertex_sin));
    obj->collider.vertices[0].y = obj->origin.y + ((-obj->width / 2) * vertex_sin + ((-obj->height / 2) * vertex_cos));

    obj->collider.vertices[1].x = obj->origin.x + ((obj->width / 2) * vertex_cos - ((-obj->height / 2) * vertex_sin));
    obj->collider.vertices[1].y = obj->origin.y + ((obj->width / 2) * vertex_sin + ((-obj->height / 2) * vertex_cos));

    obj->collider.vertices[2].x = obj->origin.x + ((-obj->width / 2) * vertex_cos - ((obj->height / 2) * vertex_sin));
    obj->collider.vertices[2].y = obj->origin.y + ((-obj->width / 2) * vertex_sin + ((obj->height / 2) * vertex_cos));

    obj->collider.vertices[3].x = obj->origin.x + ((obj->width / 2) * vertex_cos - ((obj->height / 2) * vertex_sin));
    obj->collider.vertices[3].y = obj->origin.y + ((obj->width / 2) * vertex_sin + ((obj->height / 2) * vertex_cos));
}

void UpdateCollider(PhysicsObject *obj)
{
    CalculateVertices(obj);
}

bool CheckCollision(PhysicsObject objA, PhysicsObject objB)
{
    Vector2 axis;
    Projection proj1, proj2;

    // --- TEST 1: Lato orizzontale del PRIMO cubo ---
    axis = GetAxis(objA.collider.vertices[0], objA.collider.vertices[1]);
    proj1 = GetProjection(objA.collider, axis);
    proj2 = GetProjection(objB.collider, axis);
    if (proj2.min > proj1.max || proj1.min > proj2.max)
        return false;

    // --- TEST 2: Lato verticale del PRIMO cubo ---
    axis = GetAxis(objA.collider.vertices[0], objA.collider.vertices[2]);
    proj1 = GetProjection(objA.collider, axis);
    proj2 = GetProjection(objB.collider, axis);
    if (proj2.min > proj1.max || proj1.min > proj2.max)
        return false;

    // --- TEST 3: Lato orizzontale del SECONDO cubo ---
    axis = GetAxis(objB.collider.vertices[0], objB.collider.vertices[1]);
    proj1 = GetProjection(objA.collider, axis);
    proj2 = GetProjection(objB.collider, axis);
    if (proj2.min > proj1.max || proj1.min > proj2.max)
        return false;

    // --- TEST 4: Lato verticale del SECONDO cubo ---
    axis = GetAxis(objB.collider.vertices[0], objB.collider.vertices[2]);
    proj1 = GetProjection(objA.collider, axis);
    proj2 = GetProjection(objB.collider, axis);
    if (proj2.min > proj1.max || proj1.min > proj2.max)
        return false;

    return true;
}

bool CheckMouseOverlap_Internal(Vector2 mousePosition, PhysicsObject obj)
{

    Vector2 axis;
    Projection projectionObj;
    float projectionMouse;

    axis = GetAxis(obj.collider.vertices[0], obj.collider.vertices[1]);
    projectionObj = GetProjection(obj.collider, axis);

    projectionMouse = DotProduct(axis, mousePosition);

    if (projectionMouse > projectionObj.max || projectionMouse < projectionObj.min)
    {
        return false;
    }

    axis = GetAxis(obj.collider.vertices[0], obj.collider.vertices[2]);
    projectionObj = GetProjection(obj.collider, axis);

    projectionMouse = DotProduct(axis, mousePosition);

    if (projectionMouse > projectionObj.max || projectionMouse < projectionObj.min)
    {
        return false;
    }

    return true;
}

bool CheckMouseOverlap_Single(Vector2 mousePosition, PhysicsObject object)
{

    bool collision_happened = CheckMouseOverlap_Internal(mousePosition, object);

    return collision_happened;
}

int CheckMouseOverlap_Multiple(Vector2 mousePosition, PhysicsObject objects[], int *collisionInfo, int objects_length)
{
    bool overlap = false;
    int collisionInfo_index = 0;
    for (int i = 0; i < objects_length; i++)
    {
        overlap = CheckMouseOverlap_Internal(mousePosition, objects[i]);
        if (overlap)
        {
            collisionInfo[collisionInfo_index] = i;
            collisionInfo_index++;
        }
    }

    return collisionInfo_index;
}

void UpdateColliders(PhysicsObject *objects, int objects_length)
{
    for (int i = 0; i < objects_length; i++)
    {
        CalculateVertices(&objects[i]);
    }
}