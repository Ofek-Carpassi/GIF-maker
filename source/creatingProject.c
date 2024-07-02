#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/creatingProject.h"
#include "../headers/functions.h"
#include "../headers/video.h"
#include "../headers/constants.h"

int creatingProjectMain()
{
    char path[MAX_STRING_LENGTH] = {NULL_TERMINATOR};
    int isFirstTimeSaving = TRUE;
    Video* video = NULL;
    int option = 0;

    // Print the welcome message
    printf("Working on a new project.\n\n");

    // Create a new video
    video = (Video*)malloc(sizeof(Video));
    video->head = NULL; 
    video->tail = NULL;

    // Handle the user's choice
    option = NOT_CHOSEN;

    // Loop until the user chooses to exit
    while (option != EXIT)
    {
        option = getOption();
        if(option == SAVE_PROJECT && isFirstTimeSaving == TRUE)
        {
            printf("Enter the path to save the to project: ");
            scanf("%s", path);
            saveProject(video, path);
            isFirstTimeSaving = FALSE;
            continue;
        }
        handleOption(option, video);
    }
    return 0;
}