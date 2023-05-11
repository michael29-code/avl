#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
	int key;
	char stringKey[25];
	int height;
	node *left, *right;
};


int max(int a, int b)
{
	return (a > b) ? a : b;
}

int height(node *n)
{
	if(!n)
	{
		return 0;
	}
	return n->height;
}

int getBalance(node *n)
{
	if(!n)
	{
		return 0;
	}
	return (height(n->left)- height(n->right));
}

int calculateHeight(node *n)
{
	if(!n)
	{
		return 0;
	}
	return (max(height(n->left), height(n->right)) + 1);
}


node * new_node(int key ,char stringKey[])
{
	node *n = (node *)malloc(sizeof(node));
	n->key = key;
	strcpy(n->stringKey,stringKey);
	n->height = 1;
	n->left = n->right = NULL;
	return n;
}

node * rotate_right(node *y)
{
	node *x  = y->left;
	node *t2 = x->right;
	
	x->right = y;
	y->left = t2;
	
	y->height = calculateHeight(y);
	x->height = calculateHeight(x);
	
	return x;
}

node * rotate_left(node *x)
{
	node *y = x->right;
	node *t2 = y->left;
	
	y->left = x;
	x->right = t2;
	
	x->height = calculateHeight(x);
	y->height = calculateHeight(y);
	
	return y;
}

node *insert(node *n, int key, char stringKey[])
{
	if(!n)
	{
		return new_node(key,stringKey);
	}
	
	if(key < n->key)
	{
		n->left = insert(n->left,key,stringKey);
	}else if(key > n->key)
	{
		n->right = insert(n->right,key,stringKey);
	}else
	{
		return n;
	}
	
	n->height = calculateHeight(n);
	
	int balance = getBalance(n);
	
	if(balance > 1)
	{		
		if(getBalance(n->left) < 0)
		{
			n->left = rotate_left(n->left);
		}
		
		return rotate_right(n);
	}else if(balance < -1)
	{	
		if(getBalance(n->right) > 0)
		{
			n->right = rotate_right(n->right);
		}
		return rotate_left(n);
	}
	
	return n;
}



node *deleteNode(node *n, int key)
{
	if(!n)
	{
		return n;
	}
	
	if(key < n->key)
	{
		n->left = deleteNode(n->left,key);
	}else if(key > n->key)
	{
		n->right = deleteNode(n->right,key);
	}else
	{
		if(n->left == NULL || n->right == NULL)
		{
			node * temp = (n->left) ? n->left : n->right;
			
			if(temp == NULL)
			{
				temp = n;
				n = NULL;
			}else
			{
				*n = *temp;
				free(temp);
			}
		}else
		{
			node *temp = n->right;
			
			while(temp->left != NULL)
			{
				temp = temp->left;
			}
		
			n->key = temp->key;
			strcpy(n->stringKey,temp->stringKey);
			n->right = deleteNode(n->right,temp->key);
		}
	}
	
	if(!n)
	{
		return n;
	}
	
	n->height = calculateHeight(n);
	
	int balance = getBalance(n);
	
	if(balance > 1)
	{		
		if(getBalance(n->left) < 0)
		{
			n->left = rotate_left(n->left);
		}
		
		return rotate_right(n);
	}else if(balance < -1)
	{	
		if(getBalance(n->right) > 0)
		{
			n->right = rotate_right(n->right);
		}
		return rotate_left(n);
	}
	
	return n;
	
}


void inorder(node *n)
{
	if(n)
	{
		inorder(n->left);
		printf("| Key : %d | ", n->key);
		printf("String Key : %s | ", n->stringKey);
		printf("Height : %d | \n", n->height);
		inorder(n->right);
	}
}

int main()
{
	node *root = NULL;
	
	root = insert(root,10,"nomor 10"); 
	root = insert(root,30,"nomor 30"); 
	root = insert(root,20,"nomor 20"); 
	root = insert(root,40,"nomor 40"); 
	
	inorder(root);
	
	printf("\nAfter Delete 10, 30\n");
	
	root = deleteNode(root, 10);
	root = deleteNode(root, 30);
	
	inorder(root);
	return 0;
}
