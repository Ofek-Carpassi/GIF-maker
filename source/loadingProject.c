#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/loadingProject.h"
#include "../headers/video.h"
#include "../headers/functions.h"
#include "../headers/constants.h"

int loadingProjectMain()
{
    // Print the welcome message
    char path[MAX_STRING_LENGTH];
    Video* video = NULL;
    int option = 0;
    printf("Please enter the path to the project you would like to load\n");
    scanf("%s", path);

    // Create a new video
    video = loadProject(path);

    if (video == NULL)
    {
        return 1;
    }

    // Handle the user's choice
    option = NOT_CHOSEN;
    while (option != EXIT)
    {
        option = getOption();
        if(option == SAVE_PROJECT)
        {
            saveProject(video, path);
            continue;
        }
        handleOption(option, video);
    }
    return 0;
}

Video *loadProject(char* path)
{
    // Load the project from the given path
    Video* video = NULL;
    uint32_t frameCount = 0, duration = 0;
    size_t pathLength = 0, nameLength = 0;
    char *name = NULL;
    BinaryFrame* binaryFrame = NULL;
    Frame* frame = NULL;
    int frameIndex = 0;
    FILE *file = fopen(path, "rb");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return NULL;
    }

    // Read the number of frames
    fread(&frameCount, sizeof(uint32_t), ONE, file);

    // Create a new video
    video = (Video*)malloc(sizeof(Video));
    video->head = NULL;
    video->tail = NULL;
    video->frameCount = (unsigned int)frameCount;

    for (frameIndex = 0; frameIndex < frameCount; frameIndex++)
    {
        // Read the duration
        fread(&duration, sizeof(uint32_t), ONE, file);
        // Read the size of the frame data
        fread(&pathLength, sizeof(size_t), ONE, file);
        // Read the path
        path = (char*)malloc(pathLength + NULL_TERMINATOR_LENGTH); // +1 for null terminator
        fread(path, sizeof(char), pathLength, file);
        path[pathLength] = '\0'; // Null terminate the string
        // Read the size of the frame name
        fread(&nameLength, sizeof(size_t), ONE, file);
        // Read the frame name
        name = (char*)malloc(nameLength + NULL_TERMINATOR_LENGTH); // +1 for null terminator
        fread(name, sizeof(char), nameLength, file);
        name[nameLength] = NULL_TERMINATOR; // Null terminate the string
        // Create a new binary frame
        binaryFrame = (BinaryFrame*)malloc(sizeof(BinaryFrame));
        binaryFrame->duration = duration;
        binaryFrame->pathLength = pathLength;
        binaryFrame->path = path; // Directly assign the allocated path
        binaryFrame->nameLength = nameLength;
        binaryFrame->name = name; // Directly assign the allocated name
        frame = convertBinaryFrameToRegularFrame(binaryFrame);
        // Add the frame to the video
        addFrameToVideo(video, frame);
        // Free the binary frame structure after conversion
        free(binaryFrame->path);
        free(binaryFrame->name);
        free(binaryFrame);
    }
    return video; // Ensure to return the video object
}

Frame *convertBinaryFrameToRegularFrame(BinaryFrame *binaryFrame)
{
    // Save all the data from the variables in the binary frame to a local variables
    unsigned int duration = (unsigned)binaryFrame->duration;
    size_t pathLength = binaryFrame->pathLength;
    size_t nameLength = binaryFrame->nameLength;
    char* path = (char*)malloc(pathLength);
    char* name = (char*)malloc(nameLength);
    memcpy(path, binaryFrame->path, pathLength);
    memcpy(name, binaryFrame->name, nameLength);

    // Create a new frame
    Frame* frame = (Frame*)malloc(sizeof(Frame));
    frame->path = (char*)malloc(pathLength);
    frame->name = (char*)malloc(nameLength);
    frame->duration = duration;
    memcpy(frame->path, path, pathLength);
    memcpy(frame->name, name, nameLength);

    return frame;
}

void addFrameToVideo(Video* video, Frame* frame)
{
    // Create a new frame node
    FrameNode* frameNode = (FrameNode*)malloc(sizeof(FrameNode));
    frameNode->frame = frame;
    frameNode->next = NULL;

    // Add the frame node to the video
    if (video->head == NULL)
    {
        video->head = frameNode;
        video->tail = frameNode;
    }
    else
    {
        video->tail->next = frameNode;
        video->tail = frameNode;
    }
}