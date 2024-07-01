#ifndef LOADINGPROJECT_H
#define LOADINGPROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "video.h"

int loadingProjectMain();

Video *loadProject(char* path);

Frame *convertBinaryFrameToRegularFrame(BinaryFrame *binaryFrame);

void addFrameToVideo(Video* video, Frame* frame);

#endif