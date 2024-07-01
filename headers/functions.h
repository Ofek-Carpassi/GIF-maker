#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "video.h"

// Print the menu of the program
void printMenu();

// Get the user's choice
int getOption();

// Handle the user's choice
void handleOption(int option, Video *GIF);

#endif