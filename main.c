#include <stdio.h>
#include <stdlib.h>
struct node *root;
struct node *search(struct node *root, unsigned int data);
//struct node *insert(struct node *root, unsigned int k);
unsigned int ip_to_int (char * ip);
#define INVALID 0

struct node {
        unsigned int data;  
        struct node *leftChild;
        struct node *rightChild;
        int height;
    };

struct node* newNode(unsigned int data)
{
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->data = data;
	node->leftChild = node->rightChild = NULL;
	node->height = 1;
	return (node);
}
// A utility function to get maximum of two integers
int max(int a, int b);
 
// A utility function to get height of the tree
int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
// A utility function to right rotate subtree rooted with x
struct node *rightRotate(struct node *x)
{
	printf("Rotate right node 0x%08x\n",x->data);
	struct node *y = x->leftChild;
	x->leftChild = y->rightChild;
	y->rightChild = x;
	return y;
}

// A utility function to left rotate subtree rooted with x
struct node *leftRotate(struct node *x)
{
	printf("Rotate left node 0x%08x\n",x->data);
	struct node *y = x->rightChild;
	x->rightChild = y->leftChild;
	y->leftChild = x;
	return y;
}
// Get Balance factor of node N
int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->leftChild) - height(N->rightChild);
}
// Recursive function to insert data in subtree rooted
// with node and returns new root of subtree.
struct Node* insert(struct node* node, int data)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(data));
 
    if (data < node->data)
        node->leftChild  = insert(node->leftChild, data);
    else if (data > node->data)
        node->rightChild = insert(node->rightChild, data);
    else // Equal datas are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->leftChild),
                           height(node->rightChild));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && data < node->leftChild->data)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && data > node->rightChild->data)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && data > node->leftChild->data)
    {
        node->leftChild =  leftRotate(node->leftChild);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && data < node->rightChild->data)
    {
        node->rightChild = rightRotate(node->rightChild);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
// This function brings the data at root if data is present in tree.
// If data is not present, then it brings the last accessed item at
// root. This function modifies the tree and returns the new root
struct node *splay(struct node *root, unsigned int data)
{
	printf("Splay on 0x%08x,",data);
	if(root!=NULL)
		printf("root is 0x%08x\n",root->data);
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
		printf("0x%08x ", root->data);
		preOrder(root->leftChild);
		preOrder(root->rightChild);
	}
}
// Function to insert a new key k in splay tree with given root
/*struct node *insert(struct node *root, unsigned int k)
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
*/
// This method is to convert ip addresses to unsigned integer format, so we can
// perform comparison operations on it.
unsigned int ip_to_int (char * ip)
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
int main() {
	
    int num, count, searchData;
    unsigned int data;
    printf("Enter the number of addresses: ");
    scanf("%d", &num);
    char ipAddress[16];
    // for loop terminates when n is less than count
    for(count = 1; count <= num; ++count)
    {
        printf("Enter IP address:");
        scanf("%s",ipAddress);
       	//scanf("%d", &data);
       	data=ip_to_int(ipAddress);
        if(count==1)
        	root = newNode(data);
        else
			root=insert(root,data);
    }
    printf("Search for?:\n");
    scanf("%s",ipAddress);
    searchData=ip_to_int(ipAddress);
    printf("Preorder traversal of the orignal tree is ");
    preOrder(root);
    printf("\n");
    root = search(root, searchData);
    printf("Preorder traversal of the modified Splay tree is \n");
	preOrder(root);
	return 0;
	
}
