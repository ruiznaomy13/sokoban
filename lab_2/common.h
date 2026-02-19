#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define NEW_GAME 1
#define SAVE_GAME 2
#define LOAD_GAME 3
#define RESUME_GAME 4
#define EXIT 5

/*
    constants that represents objects
    makes the code more readable and intuitive
*/
#define PLAYER	'A'
#define WALL	'#'
#define BOX     'B'
#define GOAL	'G'
#define P_GOAL	'Y'
#define B_GOAL	'X'
#define EMPTY	'.'

#define MAX_STR_LENGTH 50
#endif
