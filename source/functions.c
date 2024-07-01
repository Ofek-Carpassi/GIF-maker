#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/video.h"
#include "../headers/functions.h"

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
        case 0:
            printf("\nBye!\n");
            break;
        case 1:
            addFrame(GIF);
            break;
        case 2:
            removeFrame(GIF);
            break;
        case 3:
            changeFrameIndex(GIF);
            break;
        case 4:
            changeFrameDuration(GIF);
            break;
        case 5:
            changeAllFrameDurations(GIF);
            break;
        case 6:
            listFrames(GIF);
            break;
        case 7:
            playVideo(GIF);
            break;
        default:
            printf("Invalid option\n");
            break;
    }
}