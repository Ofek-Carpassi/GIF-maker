#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/video.h"
#include "../headers/functions.h"
#include "../headers/constants.h"

void printMenu()
{
    printf("What would you like to do?\n");
    printf(" [0] Exit\n");
    printf(" [1] Add new Frame\n");
    printf(" [2] Remove a Frame\n");
    printf(" [3] Change frame index\n");
    printf(" [4] Change frame duration\n");
    printf(" [5] Change Duration of all frames\n");
    printf(" [6] List frames\n");
    printf(" [7] Play movie!\n");
    printf(" [8] Save project\n");
}

int getOption()
{
    // Get the user's choice
    int option;
    printMenu();
    scanf("%d", &option);
    return option;
}

void handleOption(int option, Video *GIF)
{
    // Handle the user's choice
    switch (option)
    {
        case EXIT:
            printf("\nBye!\n");
            break;
        case ADD_FRAME:
            addFrame(GIF);
            break;
        case REMOVE_FRAME:
            removeFrame(GIF);
            break;
        case CHANGE_FRAME_INDEX:
            changeFrameIndex(GIF);
            break;
        case CHANGE_FRAME_DURATION:
            changeFrameDuration(GIF);
            break;
        case CHANGE_ALL_FRAME_DURATIONS:
            changeAllFrameDurations(GIF);
            break;
        case LIST_FRAMES:
            listFrames(GIF);
            break;
        case SAVE_PROJECT:
            playVideo(GIF);
            break;
        default:
            printf("Invalid option\n");
            break;
    }
}