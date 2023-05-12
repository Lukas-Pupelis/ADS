#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "binaryTree.h"
#define limit 3

void menu(node_str *tree_array[], int tree_number, int capacity, int node_count[], bool is_created[]);

int main()
{
    node_str *tree_array[10] = {NULL};
    int value, tree_number = 0;
	int tree_count = 0;
	int capacity = 0;
	int node_count[10] = {0};
	bool is_created[10] = {false};
	
	system("cls");
	printf("Lukas Pupelis\n");
	printf("\n");
	printf("Binary tree\n");
	printf("\n");
	
	int input_count = 0;
	
	while(1)
	{
		printf("Set the max number of trees (no more than 3):\n");
		input_count = (scanf("%d", &tree_count));

		if ((input_count == 1) && (tree_count < (limit+1)) && (tree_count > 0) )
        {
            break;
        }
        else if (input_count == 1)
        {
            printf("A number must be between 1 and 3. Try again \n");
        }
    }
	
	printf("Set the max number of elements in a tree\n");
	scanf("%d",&capacity);
	
	system("cls");
	printf("capacity was entered\n\n");
		
	 while(1)
    {
        if(tree_count == 1)
        {
            printf ("Enter 1 to work with the tree (0 to exit the program)\n");
        }
        else
        {
            printf ("Choose a tree between 1 and %d (0 to exit the program)\n", tree_count);
        }
		scanf("%d",&tree_number);
        system("cls");

        if (tree_number == 0)
        {
            break;
        }
        else
        {
            tree_number--;
            menu(tree_array, tree_number, capacity, node_count, is_created);
        }
    }
	
	system("cls");
    printf("Program ended");
	
    return 0;
}

void menu(node_str *tree_array[], int tree_number, int capacity, int node_count[], bool is_created[])
{
    int choice = 0, value;

    while(1)
    {
		printf ("\nChoose an option for tree %d\n\n", tree_number+1);

		printf(" 1. Create tree   |	This program creates a\n");
        printf(" 2. Insert node   |	self-balancing binary\n");
        printf(" 3. Display tree  |	tree.\n");
        printf(" 4. Sort by order |	tree.\n");
        printf(" 5. Delete node   |	Press 1-7 keys;\n");
		printf(" 6. Delete tree\n");
        printf(" 7. Exit this menu\n");
		printf("\n");
		printf("Tree capacity: %d\n",capacity);
        printf("\n Enter a key:\n ");
				
		scanf("%d",&choice);
		
		system("cls");

        switch(choice)
        {
			case 1:
			if(is_created[tree_number] == false)
			{
				is_created[tree_number] = true;
				printf("Tree has been created\n");
			}
			else
			{
				printf("Tree is already created.\n");
			}
			continue;
			
			case 2:
				if(is_created[tree_number] == true)
				{
					printf("Insert the number: ");
					
					if(node_count[tree_number] < capacity)
						{
							scanf("%d", &value);
							tree_array[tree_number] = insert_node(tree_array[tree_number], value);
							node_count[tree_number]++;
						}
						else
						{	
							system("cls");
							printf("capacity reached\n");
							break;
						}
						
						system("cls");
						printf("Element was added\n");
				}
				else
				{
					printf("Tree is not initialized");
				}	
            
            continue;
                           
            case 3:
            system("cls");
            
			if(is_created[tree_number] == true)
			{
				if(node_count[tree_number] == 0)
				{
					printf("Tree is empty");
				}
				else
				{
                printf("Tree number %d representation:\n", tree_number+1);
                print_tree(tree_array[tree_number], 0);
				}
            }
			else
			{
				printf("Tree is not initialized");
			}	
			
            continue;

            case 4:
            system("cls");
           
			if(is_created[tree_number] == true)
			{
				if(node_count[tree_number] == 0)
				{
					printf("Tree is empty");
				}
				else
				{	
					printf("Printed in order: ");
					inorder(tree_array[tree_number]);
					printf("\n");    
				}
			}
			else
			{
				printf("Tree is not initialized");
			}
			
            continue;

            case 5:
            system("cls");
            
			if(is_created[tree_number] == true)
			{
				if(node_count[tree_number] > 0)
				{
					printf("Enter a number to be deleted: ");
					int delete;
					scanf("%d", &delete);
					if(find_node(tree_array[tree_number], delete))
					{
						tree_array[tree_number] = delete_node(tree_array[tree_number], delete);
						node_count[tree_number]--;
					}
					else
					{
						printf("There is no such value in the tree");
					}
				}
				else
				{
					printf("There are no nodes in the tree.\n");
				}	
			}
			else
			{
				printf("Tree is not initialized");
			}
			
            continue;

			case 6:
			system("cls");

			if(is_created[tree_number] == true)
			{
				delete_tree(tree_array[tree_number]);
				node_count[tree_number] = 0;
				system("cls");
				printf("Tree has been deleted\n");
				is_created[tree_number] = false;
			}
			else
			{
				printf("Tree is not initialized");
			}
			continue;

            case 7:
            system("cls");
            return;
        }
    }
}

