#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "binaryTree.h"	

node_str *create_node(int value)
{
    node_str *node = (node_str *) malloc(sizeof(node_str));

    node -> value = value;
    node -> left = NULL;
    node -> right = NULL;
    node -> height = 1;

    return node;
}

node_str *insert_node(node_str *node, int value)
{
    if(node == NULL)
        return create_node(value);

    if(value < node -> value)
        node -> left = insert_node(node -> left, value);

    else if(value > node -> value)
        node -> right = insert_node(node -> right, value);

    else
        return node;

    node -> height = find_height(node);


    int balance = find_balance(node);

    if(balance > 1 && value < node ->left->value)       //R rotation
        return rightRotate(node);

    if(balance < -1 && value > node -> right -> value)  //L rotation
        return leftRotate(node);

    if(balance > 1 && value > node -> left -> value)    //LR rotation
    {
        node->left = leftRotate(node -> left);
        return rightRotate(node);
    }

    if(balance < -1 && value < node -> right -> value)  //LR rotation
    {
        node->right = rightRotate(node -> right);
        return leftRotate(node);
    }

    return node;
}

node_str *leftRotate(node_str *node)
{
    node_str *head = node -> right;
    node_str *extra = head -> left;
    head -> left = node;
    node -> right = extra;
    node -> height = find_max(find_height(node -> left), find_height(node -> right)) + 1;
    head -> height = find_max(find_height(head -> left), find_height(head -> right)) + 1;

    return head;
}

node_str *rightRotate(node_str *node)
{
    node_str *head = node -> left;
    node_str *extra = head -> right;
    head -> right = node;
    node -> left = extra;
    node -> height = find_max(find_height(node -> left), find_height(node -> right)) + 1;
    head -> height = find_max(find_height(head -> left), find_height(head -> right)) + 1;

    return head;
}

node_str *delete_node(node_str *root, int value)
{
    if(root == NULL)
        return root; 

    if(value < root -> value)
        root -> left = delete_node(root -> left, value);
        
    if(value > root -> value)
        root -> right = delete_node(root -> right, value);
    else 
    {
        if((root -> left == NULL) || (root -> right == NULL))
        {
            node_str *temp = (root -> left ? root -> left : root -> right);
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
			
            free(temp);
        }
        else
        {
            node_str *temp = find_replace(root -> right);
            root -> value = temp -> value;
            root -> right = delete_node(root -> right, temp -> value);
        }

        if(root == NULL)
        {
            return root;
        }
            
        
        root -> height  = find_max(find_height(root-> left), find_height(root -> right)) + 1;

        int balance = find_balance(root);

        if(balance > 1 && find_balance(root -> left) >= 0)       //R rotation
            return rightRotate(root);

        if(balance < -1 && find_balance(root -> right) <= 0)  //L rotation
            return leftRotate(root);

        if(balance > 1 && find_balance(root -> left) < 0)    //LR rotation
        {
            root -> left = leftRotate(root -> left);
            return rightRotate(root);
        }

        if(balance < -1 && find_balance(root -> right) > 0)  //LR rotation
        {
            root -> right = rightRotate(root -> right);
            return leftRotate(root);
        }

    return root;
    }
}

node_str *find_replace(node_str *node)
{
    node_str *temp = node;
    while(temp -> left != NULL)
        temp = temp -> left;
    return temp;
}

void inorder(node_str *root)
{
    if(root == NULL)
        return;

        inorder(root -> left);
        printf("%d ", root -> value);
        inorder(root -> right);
}

bool find_node(node_str *root, int value)
{
	if(root == NULL)
        return false;

	if(value == root -> value && root != NULL)
	{
		return true;
	}
	else if (value < root -> value)
	{
		find_node((root -> left), value);
	}
	else if (value > root -> value)
	{
		find_node((root -> right), value);
	}
	else return false;
}	

void print_tree(node_str *root, int space)
{
    if(root == NULL)
        return;
		
	printf("%d\n", root -> value);
	
	printf(" ");
	
	if(root -> left)
	{	
		for(int i = 0; i < space; i++)
			printf(" ");
		
		space += 1; 
		print_tree(root -> left, space);
		
	}

	if(root -> right)
	{	
		for(int i = 0; i < space; i++)
			printf(" ");
		
		print_tree(root -> right, space);
		
	}
	
	printf("\n");
}

void delete_tree(node_str *root)
{
	free(root);
	return;
}	


int find_max(int right, int left)
{
    return (right > left) ? right : left;
}

int find_height(node_str *node)
{
    if(node == NULL)
        return 0;
    return find_max(find_height(node -> left), find_height(node -> right)) + 1;
}

int find_balance(node_str *node)
{
    if(node == NULL)
        return 0;
    return find_height(node -> left) - find_height(node -> right);
}
