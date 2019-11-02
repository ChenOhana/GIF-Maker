/*********************************
* Class: MAGSHIMIM C3			 *
* Week: 12         				 *
*                   			 *
**********************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opencv2\core\core_c.h>
#include <opencv2\highgui\highgui_c.h>
#include "view.h"
#include "linkedList.h"
#include "saveAndLoad.h"

#define ADD_FRAME 1
#define LOAD_PROJECT 2
#define REMOVE_FRAME 2
#define CHANGE_PLACE 3
#define CHANGE_DURATION 4
#define CHANGE_ALL_DURATION 5
#define SHOW_DETAILS 6
#define PLAY 7
#define SAVE 8
#define EXIT 9

int main()
{
	FrameNode* head = NULL;
	FrameNode* add = NULL;
	int choice = 0, flag = 1;

	printf("Welcome to my GIF Maker!\n\n");
	printf("Please enter your choice from the following options:\n");
	printf("1 - Create a new project\n");
	printf("2 - Load an existing project\n");
	scanf("%d", &choice);
	getchar();
	
	if (choice == LOAD_PROJECT)
	{
		flag = load(&head, &add);
	}

	if (flag)
	{
		while (choice != EXIT)
		{
			printf("\n");
			printf("Please enter your choice from the following options:\n");
			printf("1 - Add frame\n");
			printf("2 - Remove frame\n");
			printf("3 - Change place of frame\n");
			printf("4 - Change frame's duration\n");
			printf("5 - Change all frames' durations\n");
			printf("6 - Show frames' details\n");
			printf("7 - Play GIF\n");
			printf("8 - Save project\n");
			printf("9 - Exit\n");

			scanf("%d", &choice);
			getchar();

			switch (choice)
			{
			case ADD_FRAME:
				if (head == NULL)
				{
					head = createNode(head);

					if (head)
					{
						printf("Frame added!\n");
					}
				}
				else
				{
					add = createNode(head);

					if (add)
					{
						addFrame(head, add);
						printf("Frame added!\n");
					}
				}
				break;
			case REMOVE_FRAME:
				removeFrame(&head);
				break;
			case CHANGE_PLACE:
				changePlace(&head);
				break;
			case CHANGE_DURATION:
				changeDuration(head);
				break;
			case CHANGE_ALL_DURATION:
				changeAllDurations(head);
				break;
			case SHOW_DETAILS:
				showDetails(head);
				break;
			case PLAY:
				play(head);
				break;
			case SAVE:
				save(head);
				break;
			case EXIT:
				printf("Goodbye!\n");
				break;
			default:
				break;
			}
		}

		freeList(&head);
	}
	else
	{
		printf("\nGoodbye!\n\nPress any key to exit...\n");
	}

	getchar();

	return 0;
}