#include "../headers/memory_management.h"

void *Memory_Create(void *arr, int length, size_t size_of_array_content)
{

    if (length <= 0)
    {
        printf("\nMEMORY ERROR:: length is not valid! RETURNING NULL!\n");
        return NULL;
    }

    void *ptr = malloc(length * size_of_array_content);
    if (ptr == NULL)
    {
        printf("\nMEMORY ERROR: Couldn't allocate space for new array! RETURNING NULL!\n");
    }
    else
    {
        printf("\nMEMORY SUCCESS: Allocation successful.\n");
    }

    return ptr;
}

void *Memory_Expand(void *arr, int length, int amount, size_t size_of_array_content)
{

    if (amount <= 0 || length <= 0)
    {
        printf("\nMEMORY ERROR: Couldn't allocate space for new array! RETURNING OLD ARRAY!\n");
        return arr;
    }

    int new_length = length + amount;
    int newSize = new_length * size_of_array_content;

    void *newArr = realloc(arr, newSize);

    if (newArr == NULL)
    {
        printf("\nMEMORY ERROR: Couldn't allocate space for new array! RETURNING OLD ARRAY!\n");
        return arr;
    }

    printf("\nMEMORY SUCCESS: Allocation successful.\n");

    return newArr;
}

void *Memory_Shrink(void *arr, int length, int amount, size_t size_of_array_content)
{
    if (amount <= 0 || length <= 0)
    {
        printf("\nMEMORY ERROR: Couldn't allocate space for new array! RETURNING OLD ARRAY!\n");
        return arr;
    }

    int new_length = length - amount;
    int newSize = new_length * size_of_array_content;

    void *newArr = realloc(arr, newSize);

    if (newArr == NULL)
    {
        printf("\nMEMORY ERROR: Couldn't allocate space for new array! RETURNING OLD ARRAY!\n");
        return arr;
    }

    printf("\nMEMORY SUCCESS: Allocation successful.\n");

    return newArr;
}

void *Memory_Resize(void *arr, int desired_length, size_t size_of_array_content)
{
    if (desired_length <= 0)
    {
        printf("\nMEMORY ERROR: Couldn't allocate space for new array! RETURNING OLD ARRAY!\n");
        return arr;
    }

    int new_length = desired_length * size_of_array_content;
    void *newArr = realloc(arr , new_length);
    if (newArr == NULL)
    {
        printf("\nMEMORY ERROR: Couldn't allocate space for new array! RETURNING OLD ARRAY!\n");
        return arr;
    }

    printf("\nMEMORY SUCCESS: Allocation successful.\n");

    return newArr;
}