#ifndef SAVEANDLOADH
#define SAVEANDLOADH

#include "linkedList.h"

FrameNode* createNode1(char frameName[], char path[], unsigned int duration);
void save(FrameNode* head);
int load(FrameNode** head, FrameNode** add);

#endif
