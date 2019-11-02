/*********************************
* Class: MAGSHIMIM C3			 *
* Week: 12         				 *
*                   			 *
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

/*
Function will get string from user and remove '\n'.
Input: string
Output: None
*/

void myFgets(char string[])
{
	fgets(string, SIZE, stdin);

	if (strlen(string) < SIZE)
	{
		string[strcspn(string, "\n")] = 0;
	}
}

/*
Function will create new node and return its pointer.
Input: pointer to head of list
Output: pointer to node
*/

FrameNode* createNode(FrameNode* head)
{
	char frameName[SIZE] = { 0 };
	char path[SIZE] = { 0 };

	printf("\nEnter name of frame: ");
	myFgets(frameName);

	while (check(head, frameName))
	{
		printf("Name already exists!\n\n");
		printf("Enter name of frame: ");
		myFgets(frameName);
	}

	printf("Enter path of image: ");
	myFgets(path);
	FILE* image = fopen(path, "rb");

	if (!image)
	{
		printf("Image doesn't exist!\n");
		return NULL;
	}
	else
	{
		FrameNode* frameNode = (FrameNode*)malloc(sizeof(FrameNode));
		frameNode->frame = (Frame*)malloc(sizeof(Frame));
		strcpy(frameNode->frame->name, frameName);
		strcpy(frameNode->frame->path , path);
		printf("Enter frame duration: ");
		scanf("%d", &frameNode->frame->duration);
		getchar();
		frameNode->next = NULL;

		return frameNode;
	}

	fclose(image);
}

/*
Function will check if name of frame already exists.
Input: pointer to head of list, frame name
Output: desired - pointer to desired node, NULL if name doesn't exist
*/

FrameNode* check(FrameNode* head, char frameName[])
{
	FrameNode* curr = head;
	FrameNode* desired = NULL;

	while (curr)
	{
		if (!strcmp(curr->frame->name, frameName))
		{
			desired = curr;
			curr = NULL;
		}
		else if (curr->next && !strcmp(curr->next->frame->name, frameName))
		{
			desired = curr;
			curr = NULL;
		}
		else
		{
			curr = curr->next;
		}
	}

	return desired;
}

/*
Function will add node to end of list.
Input: pointer to head of list, pointer to newNode
Output: None
*/

void addFrame(FrameNode* head, FrameNode* newNode)
{
	FrameNode* curr = head;

	while (curr->next)
	{
		curr = curr->next;
	}

	curr->next = newNode;
	newNode->next = NULL;
}

/*
Function will remove node (frame) from linked list.
Input: pointer to pointer of head of list
Output: None
*/

void removeFrame(FrameNode** head)
{
	int flag = 0;
	char frameName[SIZE] = { 0 };

	printf("\nEnter name of frame to remove: ");
	myFgets(frameName);
	
	if (*head)
	{
		FrameNode* curr = *head;
		FrameNode* temp = NULL;

		if (!strcmp((*head)->frame->name, frameName))
		{
			*head = (*head)->next;
			free(curr->frame);
			free(curr);
			printf("%s removed\n", frameName);
			flag = 1;
		}
		else
		{
			while (curr->next)
			{
				if (!strcmp(curr->next->frame->name, frameName))
				{
					temp = curr->next;
					curr->next = temp->next;
					free(temp->frame);
					free(temp);
					printf("%s removed\n", frameName);
					flag = 1;
				}
				else
				{
					curr = curr->next;
				}
			}
		}
	}

	if (!flag)
	{
		printf("%s doesn't exist\n", frameName);
	}
}

/*
Function will change place of frame.
Input: pointer to pointer of head of list
Output: None
*/

void changePlace(FrameNode** head)
{
	FrameNode* prev = NULL;
	FrameNode* curr = *head;
	FrameNode* temp = *head;
	int i = 0, place = 0, length = 0, counter = 1;
	char frameName[SIZE] = { 0 };

	while (curr)
	{
		length++;
		curr = curr->next;
	}
	curr = *head;

	if (*head)
	{
		printf("\nEnter name of frame: ");
		myFgets(frameName);
		prev = check(*head, frameName);
		

		if (!prev)
		{
			printf("%s doesn't exist\n", frameName);
		}
		else if (length == 1)
		{
			printf("There's only one frame...\n");
		}
		else
		{
			while (curr)
			{
				if (curr == prev->next || (prev == *head && strcmp(frameName, prev->next->frame->name)))
				{
					curr = NULL;
				}
				else
				{
					counter++;
					curr = curr->next;
				}
			}
			curr = *head;

			printf("Enter new place for frame: ");
			scanf("%d", &place);
			getchar();

			if (place > length || place < 1)
			{
				printf("Chosen place is bigger than number of frames or smaller than one!\n");
			}
			else if (place == counter) //if trying to move to same place (move 3rd node to place 3)
			{
				printf("Place changed!\n");
			}
			else if (prev == *head && strcmp(frameName, prev->next->frame->name))
			{
				*head = (*head)->next;

				for (i = 0; i < place - 1; i++)
				{
					curr = curr->next;
				}
				prev->next = curr->next;
				curr->next = prev;
				printf("Place changed!\n");
			}
			else if (place == 1)
			{
				curr = prev->next;
				prev->next = curr->next;
				curr->next = *head;
				*head = curr;
				printf("Place changed!\n");
			}
			else
			{
				curr = prev->next;
				prev->next = curr->next;

				for (i = 0; i < place - SECOND_NODE; i++)
				{
					temp = temp->next;
				}
				curr->next = temp->next;
				temp->next = curr;
				printf("Place changed!\n");
			}
		}
	}
	else
	{
		printf("\nNo frames were added yet!\n");
	}
}

/*
Function will change a frame's duration.
Input: pointer to head of list
Output: None
*/

void changeDuration(FrameNode* head)
{
	FrameNode* curr = head;
	unsigned int duration = 0;
	int flag = 0;
	char frameName[SIZE] = { 0 };

	if (curr)
	{
		printf("\nEnter name of frame: ");
		myFgets(frameName);

		while (curr)
		{
			if (!strcmp(curr->frame->name, frameName))
			{
				printf("Enter new duration: ");
				scanf("%u", &duration);
				getchar();
				curr->frame->duration = duration;
				printf("Duration changed!\n");
				flag = 1;
				curr = NULL;
			}
			else
			{
				curr = curr->next;
			}
		}

		if (!flag)
		{
			printf("%s doesn't exist\n", frameName);
		}
	}
	else
	{
		printf("\nNo frames were added yet!\n");
	}
}

/*
Function will change all frames' durations.
Input: pointer to head of list
Output: None
*/

void changeAllDurations(FrameNode* head)
{
	FrameNode* curr = head;
	unsigned int duration = 0;
	
	if (curr)
	{
		printf("\nEnter new duration: ");
		scanf("%u", &duration);
		getchar();

		while (curr)
		{
			curr->frame->duration = duration;
			curr = curr->next;
		}
		printf("Durations changed!\n");
	}
	else
	{
		printf("\nNo frames were added yet!\n");
	}
}

/*
Function will print all details about each frame.
Input: pointer to head of list
Output: None
*/

void showDetails(FrameNode* head)
{
	FrameNode* curr = head;

	if (curr)
	{
		while (curr)
		{
			printf("\n%s\nPath: %s\nDuration: %d\n", curr->frame->name, curr->frame->path, curr->frame->duration);
			curr = curr->next;
		}
	}
	else
	{
		printf("\nNo frames were added yet!\n");
	}
}

/*
Function will free list's nodes from memory.
Input: pointer to pointer of head of linked list
Output: None
*/

void freeList(FrameNode** head)
{
	FrameNode* curr = *head;
	FrameNode* temp = NULL;

	while (curr)
	{
		temp = curr;
		free(temp->frame);
		free(temp);
		curr = (curr)->next;
	}
	*head = NULL;
}