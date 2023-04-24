#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int key;
	node * left,* right;
	int height;
};

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int height(node *n)
{
	if(n == NULL)
	{
		return 0;
	}
	return n->height;
}

node * new_node(int key)
{
	node *n = (node *)malloc(sizeof(node));
	n->key = key;
	n->left = n->right = NULL;
	n->height = 1;
	return n;
}

node * rotate_right(node *y)
{
	node *x = y->left;
	node *t2 = x->right;
	
	x->right = y;
	y->left = t2;
	
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	
	return x;
}

node * rotate_left(node *x)
{
	node *y = x->right;
	node *t2 = y->left;
	
	y->left = x;
	x->right = t2;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return y;
}

int get_balance(node *n)
{
	if(n == NULL)
	{
		return 0;
	}
	
	return (height(n->left) - height(n->right));
}

node * insert(node *n,int key)
{
	if(n == NULL)
	{
		return new_node(key);
	}else if(key < n->key)
	{
		n->left = insert(n->left,key);
	}else if(key > n->key)
	{
		n->right = insert(n->right,key);
	}
	
	n->height = 1 + max(height(n->left), height(n->right));
	
	int balance = get_balance(n);
	
	if(balance > 1)
	{
		if(key > n->left->key)
		{
			n->left = rotate_left(n->left);
		}
		return rotate_right(n);
	}else if(balance < -1)
	{
		if(key < n->right->key)
		{
			n->right = rotate_right(n->right);
		}
		return rotate_left(n);
	}
	
	return n;
}


node * deleteNode(node *n, int key)
{
	if(n == NULL)
	{
		return n;
	}else if(key < n->key)
	{
		n->left = deleteNode(n->left,key);
	}else if(key > n->key)
	{
		n->right = deleteNode(n->right, key);
	}else
	{
		if(n->left == NULL && n->right == NULL)
		{
			free(n);
			n = NULL;
		}else if(n->left == NULL)
		{
			node *temp = n->right;
			free(n);
			n = temp;
		}else if(n->right == NULL)
		{
			node *temp = n->left;
			free(n);
			n = temp;
		}
		else
		{
			node *temp = n->right;
			
			while(temp->left != NULL)
			{
				temp = temp->left;
			}
			
			n->key = temp->key;
			n->right = deleteNode(n->right,temp->key);			
		}
	}
	
	if(n == NULL)
	{
		return n;
	}
	
	n->height = 1 + max(height(n->left), height(n->right));
	
	int balance = get_balance(n);

	if(balance > 1)
	{
		if(get_balance(n->left) < 0)
		{
			n->left = rotate_left(n->left);
		}
		return rotate_right(n);
	}else if(balance < -1)
	{
		if(get_balance(n->right) > 0)
		{
			n->right = rotate_right(n->right);
		}
		return rotate_left(n);
	}
	
	return n;	
}

void inorder(node *n)
{
	if(n == NULL)
	{
		return;
	}
	inorder(n->left);
	printf("%d ", n->key);
	inorder(n->right);
}

int main()
{
	node * root = NULL;
	
	root = insert(root,10);
	root = insert(root,30);
	root = insert(root,40);
	root = insert(root,20);
	root = insert(root,50);
	
	inorder(root);
	
	printf("\n");
	
	root = deleteNode(root,10);
	root = deleteNode(root,20);
	root = deleteNode(root,30);
	
	inorder(root);
}
