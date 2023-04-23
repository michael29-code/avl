
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	int key;
	node *left, *right;
	int height;
};
```
Struktur **Default** pada AVL
1. Key 
2. Pointer left
3. Pointer right
4. Height
---
---

```
int max(int a,int b)
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
```

function **max** buat cari nilai tinggi diantara dua value
function **height** buat return height dari nodenya

---
---

```
node * new_node(int key)
{
	node *n = (node *)malloc(sizeof(node));
	n->key = key;
	n->left = n->right = NULL;
	n->height = 1;
	return n;
}
```
funciton new_node, default height 1 sisanya null return n

---
---


Right Rotate

```
node *rotate_right(node *y) {
    node *x = y->left;
    node *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}
```

Step 1: Simpen anak kiri dari y ke variable baru x
```
node *x = y->left;
```

Step 2: Simpen anak kanan dari x ke variable t2
```
node *t2 = x->right;
```

Step 3: Buat anak kanan x ke y dan anak kiri y ke t2
```
x->right = y;
y->left = t2;
```

Step 4: Update height y dan x
```
y->height = max(height(y->left), height(y->right)) + 1;
x->height = max(height(x->left), height(x->right)) + 1;
```

Step 5: Return new root node x
```
return x;
```

```
Before Rotation:            After Rotation:
       y                           x
      / \                         / \
     x   T3     rotate_right    T1  y
    / \                             / \
   T1  T2                          T2  T3
```

---
---


Left Rotate

```
node *rotate_left (node * x)
{
	node *y = x->right;
	node *t2 = y->left;
	
	y->left = x;
	x->right = t2;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return y;
}
```

Step 1 :

```
node *y = x->right;
```

Step 2 :

```
node *t2 = y->left;
```

Step 3 :

```
y->left = x;
x->right = t2;
```

Step 4 :

```
x->height = max(height(x->left), height(x->right)) + 1;
y->height = max(height(y->left), height(y->right)) + 1;
```

Step 5 :

```
return y;
```

```
Before Rotation:            After Rotation:
        x                            y
       / \                          / \
      T1  y      rotate_left      x   T3
         / \                      / \
        T2 T3                   T1  T2
```
---
---

function get_balance cari balance;

```
int get_balance(node *n)
{
	if(n == NULL)
	{
		return 0;
	}
	return height(n->left) - height(n->right);
}
```

---
---

Insert Node 

```
node *insert(node *n, int key) {
    if (n == NULL) {
        return new_node(key);
    }

    if (key < n->key) {
        n->left = insert(n->left, key);
    } else if (key > n->key) {
        n->right = insert(n->right, key);
    } else {
        return n;
    }

    n->height = 1 + max(height(n->left), height(n->right));

    int balance = get_balance(n);

    if (balance > 1 && key < n->left->key) {
        return rotate_right(n);
    }

    if (balance < -1 && key > n->right->key) {
        return rotate_left(n);
    }

    if (balance > 1 && key > n->left->key) {
        n->left = rotate_left(n->left);
        return rotate_right(n);
    }

    if (balance < -1 && key < n->right->key) {
        n->right = rotate_right(n->right);
        return rotate_left(n);
    }

    return n;
}
```
---


function insert

```
node *insert(node *n, int key) {
  ---
}
```

harus ada rootnya  

---
Step 1 : kalau rootnya kosong

```
if (n == NULL) {
        return new_node(key);
}
```

Step 2 : kalau tidak kosong masukin dia (recursive)

```
if (key < n->key) {
	n->left = insert(n->left, key);
} else if (key > n->key) {
	n->right = insert(n->right, key);
} else {
	return n;
}
```

Step 3 : update height node yang baru di insert

```
n->height = 1 + max(height(n->left), height(n->right));
```

Step 4 : hitung balance faktor node saat ini
```
int balance = get_balance(n);
```

Step 5: kondisi rotasi

	Step 5.1 : kalau balance factor > 1 dan key <  key node left rotate kanan (LL Rotation)

```
        z                                      y 
       / \                                   /   \
      y   T4      Right Rotate (z)          x     z
     / \          - - - - - - - - ->      /  \   /  \ 
    x   T3                               T1  T2 T3  T4
   / \
 T1   T2
```
	
```
if (balance > 1 && key < n->left->key) {
	return rotate_right(n);
}
```

	Step 5.2 : kalau balance factor < -1 dan key > key node right rotate kiri (RR Rotation)

```

     z                               y
    / \                            /   \ 
   T1  y     Left Rotate(z)       z     x
      / \   - - - - - - - ->    / \   / \
     T2 x                      T1 T2 T3 T4
       / \
     T3  T4
```
	
```
if (balance < -1 && key > n->right->key) {
	return rotate_left(n);
}
```

	Step 5.3 : kalau balance factor > 1 dan key > key node left ,node left rotate ke kiri dan rotate ke kanan
	
```
if (balance > 1 && key > n->left->key) {
	n->left = rotate_left(n->left);
	return rotate_right(n);
}
```

	Step 5.4 : kalau balance factor < -1 dan key < key node right , node right rotate ke kanan dan rotate ke kiri
	
```
if (balance < -1 && key < n->right->key) {
	n->right = rotate_right(n->right);
	return rotate_left(n);
}
```

Step 6 : return n
```
return n;
```

---
---

function delete

```
node *deleteNode(node *n, int key) {
    if (n == NULL) {
        return n;
    }

    if (key < n->key) {
        n->left = deleteNode(n->left, key);
    } else if (key > n->key) {
        n->right = deleteNode(n->right, key);
    } else {
        if (n->left == NULL || n->right == NULL) {
            node *temp = n->left ? n->left : n->right;

            if (temp == NULL) {
                temp = n;
                n = NULL;
            } else {
                *n = *temp;
                free(temp);
            }
        } else {
            node *temp = n->right;

            while (temp->left != NULL) {
                temp = temp->left;
            }

            n->key = temp->key;
            n->right = deleteNode(n->right, temp->key);
        }
    }

    if (n == NULL) {
        return n;
    }

    n->height = 1 + max(height(n->left), height(n->right));

    int balance = get_balance(n);

    if (balance > 1 && get_balance(n->left) >= 0) {
        return rotate_right(n);
    }

    if (balance > 1 && get_balance(n->left) < 0) {
        n->left = rotate_left(n->left);
        return rotate_right(n);
    }

    if (balance < -1 && get_balance(n->right) <= 0) {
        return rotate_left(n);
    }

    if (balance < -1 && get_balance(n->right) > 0) {
        n->right = rotate_right(n->right);
        return rotate_left(n);
    }

    return n;
}
```
---


```
node *deleteNode(node *n, int key) {

}
```

sama seperti insert delete node kudu bawa rootnya

Step 1 :
```
if (n == NULL) {
	return n;
}
```

cek dia kosong apa nda

Step 2 :
```
if (key < n->key) {
	n->left = deleteNode(n->left, key);
} else if (key > n->key) {
	n->right = deleteNode(n->right, key);
} else {
	if (n->left == NULL || n->right == NULL) {
		node *temp = n->left ? n->left : n->right;

		if (temp == NULL) {
			temp = n;
			n = NULL;
		} else {
			*n = *temp;
			free(temp);
		}
	} else {
		node *temp = n->right;

		while (temp->left != NULL) {
			temp = temp->left;
		}

		n->key = temp->key;
		n->right = deleteNode(n->right, temp->key);
	}
}
```

	step 2.1 : kalau key < dari nilai node saat ini dia ke kiri jadii rekursif dan tetap mencari
	
```
if (key < n->key) {
	n->left = deleteNode(n->left, key);
} 
```
	Step 2.2: kalau si key > dari nilai node saat ini dia ke kanan jadi rekursif dan tetap mencari
```
else if (key > n->key) {
	n->right = deleteNode(n->right, key);
} 
``` 
	Step 2.3: kalau sudah mentok dan ketemu
```
else {
	if (n->left == NULL || n->right == NULL) {
		node *temp = n->left ? n->left : n->right;

		if (temp == NULL) {
			temp = n;
			n = NULL;
		} else {
			*n = *temp;
			free(temp);
		}
	} else {
		node *temp = n->right;

		while (temp->left != NULL) {
			temp = temp->left;
		}

		n->key = temp->key;
		n->right = deleteNode(n->right, temp->key);
	}
}
```
		Step 2.3.1 kalau dia punya child di salah satu  kiri / kanan
```
	if (n->left == NULL || n->right == NULL) {
		node *temp = n->left ? n->left : n->right;

		if (temp == NULL) {
			temp = n;
			n = NULL;
		} else {
			*n = *temp;
			free(temp);
		}
	} 
```
			Step 2.3.1.1 cari kiri / kanannya yang NULL (if else)\
			kalau si left maka temp jadi left berlaku sebaliknya
```
		node *temp = n->left ? n->left : n->right;
```
			Step 2.3.1.2 : kalau dia nda ada anak sama sekali
```
		if (temp == NULL) {
			temp = n;
			n = NULL;
		}
```
			Step 2.3.1.3 : kalau dia ada anak kiri/kanan
```
		else {
			*n = *temp;
			free(temp);
		}
```
		Step 2.3.2 : kalau semisalkan dia punya dua child
```
	else {
		node *temp = n->right;

		while (temp->left != NULL) {
			temp = temp->left;
		}

		n->key = temp->key;
		n->right = deleteNode(n->right, temp->key);
	}
```
			Step 2.3.2.1 : cari succesor
```
		node *temp = n->right;

		while (temp->left != NULL) {
			temp = temp->left;
		}
```
			Step 2.3.2.2 : replace n->key dengan value temp->key
```
		n->key = temp->key;
```
			Step 2.3.2.3 : remove
```
		n->right = deleteNode(n->right, temp->key);
```