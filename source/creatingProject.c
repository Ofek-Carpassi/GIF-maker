#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/creatingProject.h"
#include "../headers/functions.h"
#include "../headers/video.h"

int creatingProjectMain()
{
    // Print the welcome message
    printf("Working on a new project.\n\n");
    char path[100];
    int isFirstTimeSaving = 0;

    // Create a new video
    Video* video = (Video*)malloc(sizeof(Video));
    video->head = NULL; 
    video->tail = NULL;

    // Handle the user's choice
    int option = -1;

    // Loop until the user chooses to exit
    while (option != 0)
    {
        option = getOption();
        if(option == 8 && isFirstTimeSaving == 0)
        {
            printf("Enter the path to save the to project: ");
            scanf("%s", path);
            saveProject(video, path);
            isFirstTimeSaving = 1;
            continue;
        }
        handleOption(option, video);
    }
    return 0;
}