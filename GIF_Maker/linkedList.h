#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE
#define SECOND_NODE 2
#define SIZE 100

// Frame struct
typedef struct Frame
{
	char name[SIZE];
	char path[SIZE];
	unsigned int duration;
} Frame;

// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

void myFgets(char string[]);
FrameNode* createNode(FrameNode* head);
FrameNode* check(FrameNode* head, char frameName[]);
void addFrame(FrameNode* head, FrameNode* newNode);
void removeFrame(FrameNode** head);
void changePlace(FrameNode** head);
void changeDuration(FrameNode* head);
void changeAllDurations(FrameNode* head);
void showDetails(FrameNode* head);
void freeList(FrameNode** head);

#endif
