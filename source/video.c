#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> // Include for Sleep
#include "../headers/video.h"

void playVideo(Video* video)
{
    // Save the head of the list
    FrameNode* current = video->head;

    // Print the video GIF_REPEAT times
    for (int i = 0; i < GIF_REPEAT; i++)
    {
        // While the current frame is not NULL - we haven't reached the end of the list
        while (current != NULL)
        {
            // Print the frame details
            printf("Frame: %s\n", current->frame->name);
            printf("Address: %p\n", current->frame);
            printf("Duration: %d ms\n", current->frame->duration);
            printf("\n");

            // Wait for the duration of the frame * 1000 (to convert to seconds)
            Sleep(current->frame->duration * 1000);

            // Move to the next frame
            current = current->next;
        }
        // Reset the current frame to the head of the list
        current = video->head;
    }
}

void addFrame(Video* video)
{
    printf("*** Creating new frame ***\n");

    // Get the path of the frame
    char path[100];
    printf("Please insert frame path:\n");
    scanf("%s", path);

    // Make sure it's a png and not jpeg or something else
    if(strstr(path, ".png") == NULL)
    {
        printf("Invalid path! Frame will not be added\n\n");
        return;
    }

    FILE* tmpFile = fopen(path, "rb");
    if(tmpFile == NULL)
    {
        printf("Invalid path! Frame will not be added\n\n");
        return;
    }
    fclose(tmpFile);

    // Get the duration of the frame
    int duration;
    printf("Please insert frame duration (in milliseconds):\n");
    scanf("%d", &duration);

    /* Make sure the duration is valid */
    if (duration <= 0)
    {
        printf("Invalid duration! Frame will not be added\n\n");
        return;
    }

    // Get the name of the frame
    char name[100];
    printf("Please choose a name for that frame:\n");
    scanf("%s", name);

    /* Make sure the name is valid */
    while (findFrame(video, name) != NULL)
    {
        printf("The name is already taken, please enter another name:\n");
        scanf("%s", name);
    }

    // Allocate memory for the frame and the frame path and name
    Frame* frame = (Frame*)malloc(sizeof(Frame));
    frame->path = (char*)malloc(strlen(path) + 1);
    frame->name = (char*)malloc(strlen(name) + 1);

    // Copy the path, duration and name to the frame
    strcpy(frame->path, path);
    frame->duration = duration;
    strcpy(frame->name, name);

    // Create a new frame node and add it to the video
    FrameNode* node = (FrameNode*)malloc(sizeof(FrameNode));
    node->frame = frame;
    node->next = NULL;

    // If the video is empty, set the head and tail to the new node
    if (video->head == NULL)
    {
        video->head = node;
        video->tail = node;
    }
    // Otherwise, add the new node to the end of the list
    else
    {
        video->tail->next = node;
        video->tail = node;
    }

    // Increment the frame count
    video -> frameCount++;

    printf("\n");
}

FrameNode* findFrame(Video* video, char* name)
{
    // Iterate over the frames in the video
    FrameNode* current = video->head;
    while (current != NULL)
    {
        // If the name of the current frame is the same as the name we're looking for, return the frame node
        if (strcmp(current->frame->name, name) == 0)
            return current;
        // Move to the next frame
        current = current->next;
    }
    return NULL;
}

void removeFrame(Video* video)
{
    // Get the name of the frame to remove
    char name[100];
    printf("Enter the name of the frame you wish to erase\n");
    scanf("%s", name);

    // Iterate over the frames in the video
    FrameNode* current = video->head;
    FrameNode* previous = NULL;
    while (current != NULL)
    {
        // If the name of the current frame is the same as the name we're looking for
        if (strcmp(current->frame->name, name) == 0)
        {
            // If the frame is the head of the list
            if (previous == NULL)
                // Set the head of the list to the next frame
                video->head = current->next;
            else
                // Set the next of the previous frame to the next of the current frame
                previous->next = current->next;

            // Free the memory of the frame and the frame node
            free(current->frame->name);
            free(current->frame->path);
            free(current->frame);
            free(current);

            // Decrement the frame count
            video -> frameCount--;

            printf("\n");
            return;
        }
        // Move to the next frame
        previous = current;
        current = current->next;
    }
    // If the frame was not found
    printf("The frame was not found\n\n");
}

void listFrames(Video* video)
{
    printf("\t\tName\t\tDuration\t\tPath\n");

    // Iterate over the frames in the video and print their details
    FrameNode* current = video->head;
    while (current != NULL)
    {
        // Print the name, duration and path of the frame
        printf("\t\t%s\t\t%d ms\t\t\t%s\n", current->frame->name, current->frame->duration, current->frame->path);

        // Move to the next frame
        current = current->next;
    }
    printf("\n");
}

void changeFrameIndex(Video* video)
{
    // Get the name of the frame to change the index of
    char name[100];
    printf("Enter the name of the frame\n");
    scanf("%s", name);

    // Get the new index
    int newIndex;
    printf("Enter the new index in the movie you wish to place the frame\n");
    scanf("%d", &newIndex);

    // Make sure the index is valid
    while (newIndex < 1 || newIndex > video->frameCount)
    {
        printf("Invalid index! Please enter a number between 1 and %d\n", video->frameCount);
        scanf("%d", &newIndex);
    }

    // Iterate over the frames in the video
    FrameNode* current = video->head;
    FrameNode* previous = NULL;

    while (current != NULL)
    {
        // If the name of the current frame is the same as the name we're looking for
        if (strcmp(current->frame->name, name) == 0)
        {
            // If the frame is the head of the list
            if (previous == NULL)
                // Set the head of the list to the next frame
                video->head = current->next;
            else
                // Set the next of the previous frame to the next of the current frame
                previous->next = current->next;


            // Save the head of the list
            FrameNode* temp = video->head;

            // Find the frame before the new index
            for (int i = 1; i < newIndex - 1; i++)
                temp = temp->next;

            // If the new index is 1, set the current frame as the head of the list
            if (newIndex == 1)
            {
                current->next = video->head;
                video->head = current;
            }
            // Otherwise, set the current frame as the next of the frame before the new index
            else
            {
                current->next = temp->next;
                temp->next = current;
            }

            printf("\n");
            return;
        }
        // Move to the next frame
        previous = current;
        current = current->next;
    }

    printf("The frame was not found\n\n");
}

void changeFrameDuration(Video* video)
{
    // Get the name of the frame to change the duration of
    char name[100];
    printf("Enter the name of the frame\n");
    scanf("%s", name);

    // Get the new duration
    int newDuration;
    printf("Enter the new duration\n");
    scanf("%d", &newDuration);

    // Make sure the duration is valid
    while (newDuration <= 0)
    {
        printf("Invalid duration! Please enter a positive number\n");
        scanf("%d", &newDuration);
    }

    // Iterate over the frames in the video
    FrameNode* current = video->head;
    while (current != NULL)
    {
        // If the name of the current frame is the same as the name we're looking for
        if (strcmp(current->frame->name, name) == 0)
        {
            // Change the duration of the frame
            current->frame->duration = newDuration;
            printf("\n");
            return;
        }
        // Move to the next frame
        current = current->next;
    }

    printf("The frame was not found\n\n");
}

void changeAllFrameDurations(Video* video)
{
    // Get the new duration
    int newDuration;
    printf("Enter the new duration\n");
    scanf("%d", &newDuration);
    
    // Make sure the duration is valid
    while (newDuration <= 0)
    {
        printf("Invalid duration! Please enter a positive number\n");
        scanf("%d", &newDuration);
    }

    // Iterate over the frames in the video and change their duration
    FrameNode* current = video->head;
    while (current != NULL)
    {
        // Change the duration of the frame
        current->frame->duration = newDuration;
        // Move to the next frame
        current = current->next;
    }

    printf("\n");
}

void saveProject(Video* video, char* path) // Corrected typo in comment
{
    FILE *file = fopen(path, "wb");
    if(!file)
    {
        printf("Error opening file\n");
        return;
    }

    // Write the header of the file
    fwrite(&video->frameCount, sizeof(video->frameCount), 1, file);

    // Iterate over the frames in the video and write their details to the file
    FrameNode* current = video->head;
    while (current != NULL)
    {
        BinaryFrame binaryFrame = convertRegularFrameToBinaryFrame(current->frame); // Corrected function name typo

        // Write duration directly as binary
        fwrite(&binaryFrame.duration, sizeof(binaryFrame.duration), 1, file);

        // Write pathLength directly as binary
        fwrite(&binaryFrame.pathLength, sizeof(binaryFrame.pathLength), 1, file);

        // Write path
        fwrite(binaryFrame.path, binaryFrame.pathLength, 1, file);

        // Write nameLength directly as binary
        fwrite(&binaryFrame.nameLength, sizeof(binaryFrame.nameLength), 1, file);

        // Write name
        fwrite(binaryFrame.name, binaryFrame.nameLength, 1, file);

        // Free allocated memory
        free(binaryFrame.path);
        free(binaryFrame.name);

        current = current->next; // Move to the next frame
    }

    fclose(file);
    printf("Project saved successfully\n");
}

BinaryFrame convertRegularFrameToBinaryFrame(Frame* frame)
{
    BinaryFrame binaryFrame;
    binaryFrame.duration = frame->duration;
    binaryFrame.pathLength = strlen(frame->path) + 1; // +1 for null terminator
    binaryFrame.path = (char*)malloc(binaryFrame.pathLength);
    if (binaryFrame.path != NULL) {
        strcpy(binaryFrame.path, frame->path);
    }
    binaryFrame.nameLength = strlen(frame->name) + 1; // +1 for null terminator
    binaryFrame.name = (char*)malloc(binaryFrame.nameLength);
    if (binaryFrame.name != NULL) {
        strcpy(binaryFrame.name, frame->name);
    }
    return binaryFrame;
}