// Compilation: gcc -o MagshimimMovieMaker source/main.c source/creatingProject.c source/loadingProject.c source/functions.c source/video.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/loadingProject.h"
#include "../headers/creatingProject.h"

// Flags for the base menu
#define CREATE_PROJECT 0
#define LOAD_PROJECT 1

// Function prototypes
int baseMenu();
void handleBaseOption(int option);

int main()
{  
    // Get the user's choice (create project or load project)
    int option;
    option = baseMenu();

    // Handle the user's choice
    handleBaseOption(option);

    getchar();
    getchar();
    return 0;
}

int baseMenu()
{
    int option;

    // Print the base menu
    printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
    printf(" [0] Create a new project\n");
    printf(" [1] Load existing project\n");

    // Get the user's choice
    scanf("%d", &option);

    // Return the user's choice
    return option;
}

void handleBaseOption(int option)
{
    // Handle the user's choice
    switch (option)
    {
        // Create a new project by calling the creatingProjectMain function
        case CREATE_PROJECT:
            creatingProjectMain();
            break;
        // Load an existing project by calling the loadingProjectMain function
        case LOAD_PROJECT:
            loadingProjectMain();
            break;
        // If the user's choice is invalid, print an error message
        default:
            printf("Invalid option, please try again.\n");
            break;
    }
}