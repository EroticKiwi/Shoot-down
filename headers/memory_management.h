#pragma once

#include <stdlib.h>
#include <stdio.h>

void *Memory_Create(void *arr, int length, size_t size_of_array_content);
void *Memory_Expand(void *arr, int length, int amount, size_t size_of_array_content);
void *Memory_Shrink(void *arr, int length, int amount, size_t size_of_array_content);