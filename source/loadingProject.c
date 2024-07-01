#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/loadingProject.h"
#include "../headers/video.h"
#include "../headers/functions.h"

int loadingProjectMain()
{
    // Saving and creating a new project isn't implemented yet - loading project and creating project are the same

    // Print the welcome message
    char path[100];
    printf("Please enter the path to the project you would like to load\n");
    scanf("%s", path);

    // Create a new video
    Video* video = loadProject(path);

    // Handle the user's choice
    int option = -1;
    while (option != 0)
    {
        option = getOption();
        if(option == 8)
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
    FILE *file = fopen(path, "rb");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return NULL;
    }

    // Read the number of frames
    uint32_t frameCount;
    fread(&frameCount, sizeof(uint32_t), 1, file);

    // Create a new video
    Video* video = (Video*)malloc(sizeof(Video));
    video->head = NULL;
    video->tail = NULL;
    video->frameCount = (unsigned int)frameCount;

    for (int i = 0; i < frameCount; i++)
    {
        // Read the duration
        uint32_t duration;
        fread(&duration, sizeof(uint32_t), 1, file);
        // Read the size of the frame data
        size_t pathLength;
        fread(&pathLength, sizeof(size_t), 1, file);
        // Read the path
        char* path = (char*)malloc(pathLength + 1); // +1 for null terminator
        fread(path, sizeof(char), pathLength, file);
        path[pathLength] = '\0'; // Null terminate the string
        // Read the size of the frame name
        size_t nameLength;
        fread(&nameLength, sizeof(size_t), 1, file);
        // Read the frame name
        char* name = (char*)malloc(nameLength + 1); // +1 for null terminator
        fread(name, sizeof(char), nameLength, file);
        name[nameLength] = '\0'; // Null terminate the string
        // Create a new binary frame
        BinaryFrame* binaryFrame = (BinaryFrame*)malloc(sizeof(BinaryFrame));
        binaryFrame->duration = duration;
        binaryFrame->pathLength = pathLength;
        binaryFrame->path = path; // Directly assign the allocated path
        binaryFrame->nameLength = nameLength;
        binaryFrame->name = name; // Directly assign the allocated name
        Frame *frame = convertBinaryFrameToRegularFrame(binaryFrame);
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