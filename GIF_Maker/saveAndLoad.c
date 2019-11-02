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
#include "saveAndLoad.h"

/*
Function will create new node and return its pointer.
Input: frameName, path, duration
Output: pointer to node
*/

FrameNode* createNode1(char frameName[], char path[], unsigned int duration)
{
	FrameNode* frameNode = (FrameNode*)malloc(sizeof(FrameNode));
	frameNode->frame = (Frame*)malloc(sizeof(Frame));
	strcpy(frameNode->frame->name, frameName);
	strcpy(frameNode->frame->path, path);
	frameNode->frame->duration = duration;
	frameNode->next = NULL;
	
	return frameNode;
}

/*
Function will save project into text file.
Input: pointer to head of list
Output: None
*/

void save(FrameNode* head)
{
	FILE* data = NULL;
	FrameNode* curr = head;
	int length = 0;
	char path[SIZE] = { 0 };

	printf("\nEnter the path where you want to save the project: ");
	myFgets(path);

	if (!fopen(path, "a") || !strstr(path, ".txt"))
	{
		printf("Wrong path! Please include file extension in path\n");
		printf("Usage: <C:/path/file_name.txt>\n");
	}
	else
	{
		data = fopen(path, "a");

		while (curr)
		{
			length++;
			curr = curr->next;
		}
		curr = head;
		fprintf(data, "%d" "%s", length, "\n");

		while (curr)
		{
			fprintf(data, "%s" "%s", curr->frame->name, "\n");
			fprintf(data, "%s" "%s", curr->frame->path, "\n");
			fprintf(data, "%u" "%s", curr->frame->duration, "\n");
			curr = curr->next;
		}
		printf("Project saved!\n");
		fclose(data);
	}
}

/*
Function will load project from text file.
Input: pointer to pointer of head of list, pointer to pointer of add
Output: None
*/

int load(FrameNode** head, FrameNode** add)
{
	FILE* data = NULL;
	int i = 0, flag = 0, length = 0;
	unsigned int duration = 0;
	char frameName[SIZE] = { 0 };
	char path[SIZE] = { 0 };
	char size[SIZE] = { 0 };

	printf("Enter the path you want to load your project from: ");
	myFgets(path);

	if (!fopen(path, "r") || !strstr(path, ".txt"))
	{
		printf("\nWrong path! Please include file extension in path\n");
		printf("Usage: <C:/path/file_name.txt>\n");
	}
	else
	{
		data = fopen(path, "r");
		fgets(size, SIZE, data);
		size[strcspn(size, "\n")] = 0;
		length = atoi(size);

		for (i = 0; i < length; i++)
		{
			fgets(frameName, SIZE, data);
			frameName[strcspn(frameName, "\n")] = 0;
			fgets(path, SIZE, data);
			path[strcspn(path, "\n")] = 0;
			fgets(size, SIZE, data);
			size[strcspn(size, "\n")] = 0;
			duration = atoi(size);

			if (*head == NULL)
			{
				*head = createNode1(frameName, path, duration);
			}
			else
			{
				*add = createNode1(frameName, path, duration);
				addFrame(*head, *add);
			}
		}
		flag = 1;
		printf("Project loaded successfully!\n");
		fclose(data);
	}

	return flag;
}