#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 100
#define TRUE 1
#define FALSE 0
enum {
    NOT_CHOSEN = -1,
    EXIT,
    ADD_FRAME,
    REMOVE_FRAME,
    CHANGE_FRAME_INDEX,
    CHANGE_FRAME_DURATION,
    CHANGE_ALL_FRAME_DURATIONS,
    LIST_FRAMES,
    PLAY_VIDEO,
    SAVE_PROJECT
};
#define ONE 1
#define ZERO 0
#define NULL_TERMINATOR_LENGTH 1
#define NULL_TERMINATOR '\0'
#define CREATE_PROJECT 0
#define LOAD_PROJECT 1
#define MILISECONDS_TO_SECONDS 1000
#define COMPARE_EQUAL 0


#endif