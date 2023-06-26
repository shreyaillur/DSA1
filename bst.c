#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct node
{
  int key;
  struct node *left;
  struct node *right;
};

struct node *newnode(int item)
{
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = item;
  temp->left = temp->right = NULL;
  return temp;
}
void inorder(struct node *root)
{
  if (root != NULL)
  {
    inorder(root->left);
    printf(" %d ", root->key);
    inorder(root->right);
  }
}
struct node *insert(struct node *root, int key)
{
  if (root == NULL)
    return newnode(key);
  if (key < root->key)
    root->left = insert(root->left, key);
  else
    root->right = insert(root->right, key);
  return root;
}
struct node *minValueNode(struct node *node)
{
    struct node *current =node;
    while(current->left!=NULL)
    current=current->left;
        return current ;

}
struct node *deleteNode(struct node *root,int key)
{
    if (root==NULL)
        return root;
    if(key<root->key)
        root-> left=deleteNode(root-> left,key);
    else if (key > root-> key)

root -> right = deleteNode(root-> right,key);
else
{
   if(root->left==NULL)
   {
       struct node *temp= root->right;
       free(root);
       return temp;
   }
   else if ( root -> right ==NULL)
   {
       struct node *temp =root-> left;
       free(root);
       return temp;
   }
struct node *temp=minValueNode(root->right);
   root->key=temp->key;
   root->right=deleteNode(root->right,temp->key);
}
return root ;
}



void preorder(struct node *root)
{
  if (root != NULL)
  {
    printf(" %d ", root->key);
    preorder(root->left);
    preorder(root->right);
  }
}

void postorder(struct node *root)
{
  if (root != NULL)
  {
    postorder(root->left);
    postorder(root->right);
    printf(" %d ", root->key);
  }
}





int main()
{
  struct node *root = NULL;
  root = insert(root, 50);
  root = insert(root, 15);
  root = insert(root, 62);
  root = insert(root, 5);
  root = insert(root, 20);
  root = insert(root, 58);
  root = insert(root, 91);
  root = insert(root, 8);
  root = insert(root, 37);
  root = insert(root, 60);
  root = insert(root, 24);
  printf("\n\nInorder traversal of the binary search tree: \n");
  inorder(root);

  printf("\n\nPreorder traversal of the binary search tree: \n");
  preorder(root);

  printf("\n\nPostorder traversal of the binary search tree: \n");
  postorder(root);

  root=deleteNode(root,50);
   printf("\n\nInorder traversal of the binary search tree: \n");
  inorder(root);

  printf("\n\nPreorder traversal of the binary search tree: \n");
  preorder(root);

  printf("\n\nPostorder traversal of the binary search tree: \n");
  postorder(root);

  return 0;
}
