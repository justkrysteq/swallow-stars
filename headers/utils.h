#pragma once

#include <stdio.h>

/**
 * **Generates a random number between min and max**
 *
 * Uses /dev/urandom to generate a random number between min and max (inclusive)
 *
 * *Parameters:*
 * - **min**: *minimum value that the random number can be*
 * - **max**: *maximum value that the random number can be*
 *
 * *Returns:* random number
 */
int get_random(int min, int max);

/**
 * **Trims a string**
 *
 * By removing all spaces and tabs from the beginning
 * If the string contains a space, tab, # or newline, everything after it will be removed
 *
 * *Parameters:*
 * - **string**: *string to be trimmed*
 */
void trim(char *string);
