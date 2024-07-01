#ifndef VIDEO_H
#define VIDEO_H

#define GIF_REPEAT 5

#include <stdint.h>

// A struct to represent a frame in a video
typedef struct Frame
{
	char* path;  
	char* name;
	unsigned int duration;
} Frame;

// A struct to represent a node in a linked list of frames
typedef struct FrameNode
{
    Frame* frame;
    struct FrameNode* next;
} FrameNode;

// A struct to represent a video - save the head and tail of the linked list of frames and the number of frames in the video
typedef struct Video
{
    FrameNode* head;
    FrameNode* tail;
    unsigned int frameCount;
} Video;

typedef struct BinaryFrame {
    uint32_t duration; // Duration of the frame in milliseconds
    size_t pathLength; // Length of the path to the frame
    char* path; // Path to the frame
    size_t nameLength; // Length of the name of the frame
    char* name; // Name of the frame
} BinaryFrame;

typedef struct BinaryVideo {
    uint32_t frameCount; // Number of frames in the video
    BinaryFrame* frames; // Pointer to the array of frames
} BinaryVideo;

/**
 * @brief Add a frame to a video
 * 
 * @param video The video to add the frame to
 * @param frame The frame to add
 */
void addFrame(Video* video);

/**
 * @brief Find a specific frame in a video
 * 
 * @param video The video to search in
 * @param name The name of the frame to search for
 * @return FrameNode* A pointer to the frame node if found, NULL otherwise
 */
FrameNode* findFrame(Video* video, char* name);

/**
 * @brief Remove a frame from a video
 * 
 * @param video The video to remove the frame from
 */
void removeFrame(Video* video);

/**
 * @brief List all the frames in a video
 * 
 * @param video The video to list the frames of
 */
void listFrames();

/**
 * @brief Change the index of a frame in a video
 * 
 * @param video The video to change the frame index in
 */
void changeFrameIndex(Video* video);

/**
 * @brief Change the duration of a frame in a video
 * 
 * @param video The video to change the frame duration in
 */
void changeFrameDuration(Video* video);

/**
 * @brief Change the duration of all the frames in a video
 * 
 * @param video The video to change the frame durations in
 */
void changeAllFrameDurations(Video* video);

/**
 * @brief Play a video
 * 
 * @param video The video to play
 */
void playVideo(Video* video);

/**
 * @brief Save a video to a file
 * 
 * @param video The video to save
 */
void saveProject(Video* video, char* path);

BinaryFrame convertRegularFrameToBinaryFrame(Frame* frame);

#endif