#include <stdio.h>
#include <stdlib.h>
struct node *root;
struct node *search(struct node *root, int data);
struct node *insert(struct node *root,int k);
struct node {
        int data;  
        struct node *leftChild;
        struct node *rightChild;
    };

struct node* newNode(int data)
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
// This function brings the data at root if key is present in tree.
// If key is not present, then it brings the last accessed item at
// root. This function modifies the tree and returns the new root
struct node *splay(struct node *root, int data)
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
struct node *search(struct node *root, int data)
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
int main() {
	
    int num, count,data, searchData;
    printf("Enter the number of integers: ");
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
    printf("Preorder traversal of the orignal tree is ");
    preOrder(root);
    printf("\n");
    root = search(root, searchData);
    printf("Preorder traversal of the modified Splay tree is \n");
	preOrder(root);
	return 0;
	
	
	/*struct node *root = newNode(100);
    root->leftChild = newNode(50);
    root->rightChild = newNode(200);
    root->leftChild->leftChild = newNode(40);
    root->leftChild->leftChild->leftChild = newNode(30);
    root->leftChild->leftChild->leftChild->leftChild = newNode(20);
	printf("Preorder traversal of the orignal tree is \n");
    preOrder(root); 
    root = search(root, 20);
    root = search(root, 20);
    printf("Preorder traversal of the modified Splay tree is \n");
	preOrder(root);
	return 0;*/
}
/*struct node* search(int data){
   struct node *current = root;
   printf("Visiting elements: ");
   while(current->data != data){
      if(current != NULL) {
         printf("%d ",current->data);
         //go to left tree
         if(current->data > data){
            current = current->leftChild;
         }//else go to right tree
         else {               
            current = current->rightChild;
         }
         //not found
         if(current == NULL){
            return NULL;
         }
      }                                       
   }
   return current;
}
*/
/*void insert(int data,struct node* root) {
   struct node *tempNode = (struct node*) malloc(sizeof(struct node));
   struct node *current;
   struct node *parent;
   tempNode->data = data;
   tempNode->leftChild = NULL;
   tempNode->rightChild = NULL;
  
   //if tree is empty
   if(root == NULL) {
   		//printf("root is null");
      	root = tempNode;
   } else {
      current = root;
      parent = NULL;
      while(1) {               
         parent = current;
         //go to left of the tree
         if(data < parent->data) {
            current = current->leftChild;               
            //insert to the left
            if(current == NULL) {
               parent->leftChild = tempNode;
               printf("%d inserted to the left\n", data);
               return;
              
            }
         }//go to right of the tree
         else {
            current = current->rightChild;
            //insert to the right
            if(current == NULL) {
               parent->rightChild = tempNode;
               printf("%d inserted to the right\n", data);
               return;
            }
         }
      }           
   }
} */
// Function to insert a new key k in splay tree with given root
struct node *insert(struct node *root, int k)
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
