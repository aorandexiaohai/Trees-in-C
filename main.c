#include <stdio.h>
#include <stdlib.h>
struct node *root;
struct node *search(struct node *root, unsigned int data);
struct node *insert(struct node *root, unsigned int k);
unsigned int ip_to_int (const char * ip);
#define INVALID 0
struct node {
        unsigned int data;  
        struct node *leftChild;
        struct node *rightChild;
    };

struct node* newNode(unsigned int data)
{
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->data = data;
	node->leftChild = node->rightChild = NULL;
	return (node);
}
// A utility function to right rotate subtree rooted with x
struct node *rightRotate(struct node *x)
{
	printf("Rotate righ node %d\n",x->data);
	struct node *y = x->leftChild;
	x->leftChild = y->rightChild;
	y->rightChild = x;
	return y;
}

// A utility function to left rotate subtree rooted with x
struct node *leftRotate(struct node *x)
{
	printf("Rotate left node %d\n",x->data);
	struct node *y = x->rightChild;
	x->rightChild = y->leftChild;
	y->leftChild = x;
	return y;
}
// This method is to convert ip addresses to unsigned integer format, so we can
// perform comparison operations on it.
unsigned int ip_to_int (const char * ip)
{
    /* The return value. */
    unsigned v = 0;
    /* The count of the number of bytes processed. */
    int i;
    /* A pointer to the next digit to process. */
    const char * start;

    start = ip;
    for (i = 0; i < 4; i++) {
        /* The digit being processed. */
        char c;
        /* The value of this byte. */
        int n = 0;
        while (1) {
            c = * start;
            start++;
            if (c >= '0' && c <= '9') {
                n *= 10;
                n += c - '0';
            }
            /* We insist on stopping at "." if we are still parsing
               the first, second, or third numbers. If we have reached
               the end of the numbers, we will allow any character. */
            else if ((i < 3 && c == '.') || i == 3) {
                break;
            }
            else {
                return INVALID;
            }
        }
        if (n >= 256) {
            return INVALID;
        }
        v *= 256;
        v += n;
    }
    return v;
}
// This function brings the data at root if key is present in tree.
// If key is not present, then it brings the last accessed item at
// root. This function modifies the tree and returns the new root
struct node *splay(struct node *root, unsigned int data)
{
	printf("Splay on %d,",data);
	if(root!=NULL)
		printf("root is %d\n",root->data);
	// Base cases: root is NULL or key is present at root
	if (root == NULL || root->data == data)
		return root;

	// Key lies in left subtree
	if (root->data > data)
	{
		// Key is not in tree, we are done
		if (root->leftChild == NULL) return root;

		// Zig-Zig (Left Left)
		if (root->leftChild->data > data)
		{
			// First recursively bring the key as root of left-left
			root->leftChild->leftChild = splay(root->leftChild->leftChild, data);

			// Do first rotation for root, second rotation is done after else
			root = rightRotate(root);
		}
		else if (root->leftChild->data < data) // Zig-Zag (Left Right)
		{
			// First recursively bring the key as root of left-right
			root->leftChild->rightChild = splay(root->leftChild->rightChild, data);

			// Do first rotation for root->left
			if (root->leftChild->rightChild != NULL)
				root->leftChild = leftRotate(root->leftChild);
		}

		// Do second rotation for root
		
		return (root->leftChild == NULL)? root: rightRotate(root);
	}
	else // Key lies in right subtree
	{
		// Key is not in tree, we are done
		if (root->rightChild == NULL) return root;

		// Zag-Zig (Right Left)
		if (root->rightChild->data > data)
		{
			// Bring the key as root of right-left
			root->rightChild->leftChild = splay(root->rightChild->leftChild, data);

			// Do first rotation for root->right
			if (root->rightChild->leftChild != NULL)
				root->rightChild = rightRotate(root->rightChild);
		}
		else if (root->rightChild->data < data)// Zag-Zag (Right Right)
		{
			// Bring the key as root of right-right and do first rotation
			root->rightChild->rightChild = splay(root->rightChild->rightChild, data);
			root = leftRotate(root);
		}

		// Do second rotation for root
		return (root->rightChild == NULL)? root: leftRotate(root);
	}
}

// The search function for Splay tree. Note that this function
// returns the new root of Splay Tree. If key is present in tree
// then, it is moved to root.
struct node *search(struct node *root, unsigned int data)
{
	return splay(root, data);
}
// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void preOrder(struct node *root)
{
	if (root != NULL)
	{
		printf("%d ", root->data);
		preOrder(root->leftChild);
		preOrder(root->rightChild);
	}
}
// Function to insert a new key k in splay tree with given root
struct node *insert(struct node *root, unsigned int k)
{
    // Simple Case: If tree is empty
    if (root == NULL) return newNode(k);
 
    // Bring the closest leaf node to root
    root = splay(root, k);
 
    // If key is already present, then return
    if (root->data == k) return root;
 
    // Otherwise allocate memory for new node
    struct node *newnode  = newNode(k);
 
    // If root's key is greater, make root as right child
    // of newnode and copy the left child of root to newnode
    if (root->data > k)
    {
        newnode->rightChild = root;
        newnode->leftChild = root->leftChild;
        root->leftChild = NULL;
    }
 
    // If root's key is smaller, make root as left child
    // of newnode and copy the right child of root to newnode
    else
    {
        newnode->leftChild = root;
        newnode->rightChild = root->rightChild;
        root->rightChild = NULL;
    }
 
    return newnode; // newnode becomes new root
}

int main() {
	
    int num, count,data, searchData;
    printf("Enter the number of addresses: ");
    scanf("%d", &num);
    
    // for loop terminates when n is less than count
    for(count = 1; count <= num; ++count)
    {
        //printf("Enter a positive integer: ");
       	scanf("%d", &data);
        if(count==1)
        	root = newNode(data);
        else
			root=insert(root,data);
    }
    printf("Search for?:\n");
    scanf("%d", &searchData);
    scanf("%d", &searchData);
    printf("Preorder traversal of the orignal tree is ");
    preOrder(root);
    printf("\n");
    root = search(root, searchData);
    printf("Preorder traversal of the modified Splay tree is \n");
	preOrder(root);
	return 0;
	
}	


