#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int imax(int m, int n)
{
   return(m > n ? m : n);
}

struct node *create_node(char *k)
{
   struct node *node = (struct node *) malloc(sizeof(struct node));
   node->key = (char *) malloc(strlen(k)+1);
   strcpy(node->key, k);
   node->h = 0;
   node->bal = 0;
   node->left = (struct node *) NULL;
   node->right = (struct node *) NULL;
   return(node);
}

void dealloc(struct node *root)
{
   if (root == (struct node *) NULL)
      return;
   dealloc(root->left);
   dealloc(root->right);
   free(root->key);
   free(root);
}

int size(struct node *root)
{
   if (root == (struct node *) NULL)
      return(0);
   else
      return(1 + size(root->left) + size(root->right));
}

int height(struct node *node)
{
   return((node) ? node->h : -1);
}

int balance_factor(struct node *node)
{
   return((node) ? height(node->left) - height(node->right) : 0);
}


struct node *search(struct node *root, char *k)
{
   if (root == (struct node *) NULL)
      return((struct node *) NULL);

   if (strcmp(k, root->key) < 0)
      return(search(root->left, k));
   else if (strcmp(k, root->key) > 0)
      return(search(root->right, k));
   else
      return(root);
}

struct node *minkey(struct node *root)
{
   if (root->left == (struct node *) NULL)
      return(root);

   return(minkey(root->left));
}

struct node *maxkey(struct node *root)
{
   if (root->right == (struct node *) NULL)
      return(root);

   return(maxkey(root->right));
}

struct node *predecessor(struct node *root, struct node *pred, 
      char *k)
{
   if (root == (struct node *) NULL)
      return((struct node *) NULL);

   if (strcmp(k, root->key) < 0)
      return(predecessor(root->left, pred, k));
   else if (strcmp(k, root->key) > 0) {
      pred = root;
      return(predecessor(root->right, pred, k));
   }
   else
      if (root->left)
         return(maxkey(root->left));

   return(pred);
}

struct node *successor(struct node *root, struct node *succ, 
      char *k)
{
   if (root == (struct node *) NULL)
      return((struct node *) NULL);

   if (strcmp(k, root->key) > 0)
      succ = successor(root->right, succ, k);
   else if (strcmp(k, root->key) < 0) {
      succ = root;
      succ = successor(root->left, succ, k);
   }
   else
      if (root->right)
         succ = minkey(root->right);

   return(succ);
}

struct node *insert(struct node *root, char *k)
{
   if (root == (struct node *) NULL) {
      root = create_node(k);
      return(root);
   }

   if (strcmp(k, root->key) < 0)
      root->left = insert(root->left, k);
   else if (strcmp(k, root->key) > 0)
      root->right = insert(root->right, k);
   else
      return(root);

   root->h = 1 + imax(height(root->left), height(root->right));
   root->bal = balance_factor(root);

   /* Left Left Case */
   if (root->bal > 1 && root->left->bal > 0)
      return(rotate_right(root));

   /* Right Right Case */
   if (root->bal < -1 && root->right->bal < 0)
      return(rotate_left(root));

   /* Left Right Case */
   if (root->bal > 1 && root->left->bal < 0) {
      root->left = rotate_left(root->left);
      return(rotate_right(root));
   }

   /* Right Left Case */
   if (root->bal < -1 && root->right->bal > 0) {
      root->right = rotate_right(root->right);
      return rotate_left(root);
   }
   
   return(root);
}

struct node *delete(struct node *root, char *k)
{
   struct node *tag;

   if (root == (struct node *) NULL) 
      return(root);

   if (strcmp(k, root->key) < 0)
      root->left = delete(root->left, k);
   else if (strcmp(k, root->key) > 0)
      root->right = delete(root->right, k);
   else {
      if (root->left == (struct node *) NULL) {
         tag = root->right;
         free(root->key);
         free(root);
         return(tag);
      }
      else if (root->right == (struct node *) NULL) {
         tag = root->left;
         free(root->key);
         free(root);
         return(tag);
      }
      tag = maxkey(root->left);
      free(root->key);
      root->key = (char *) malloc(strlen(tag->key)+1);
      strcpy(root->key, tag->key);
      root->left = delete(root->left, tag->key);      
   }

   root->h = 1 + imax(height(root->left), height(root->right));
   root->bal = balance_factor(root);

   /* Left Left Case */
   if (root->bal > 1 && root->left->bal > 0)
      return(rotate_right(root));

   /* Right Right Case */
   if (root->bal < -1 && root->right->bal < 0)
      return(rotate_left(root));

   /* Left Right Case */
   if (root->bal > 1 && root->left->bal < 0) {
      root->left = rotate_left(root->left);
      return(rotate_right(root));
   }

   /* Right Left Case */
   if (root->bal < -1 && root->right->bal > 0) {
      root->right = rotate_right(root->right);
      return rotate_left(root);
   }
   
   return(root);
}

struct node *rotate_left(struct node *root)
{
	struct node *p = root->right, *q = root->right->left;

	p->left = root;
	root->right = q;

	root->h = 1 + imax(height(root->left), height(root->right));
	p->h = 1 + imax(height(p->left), height(p->right));

   root->bal = balance_factor(root);
   p->bal = balance_factor(root);

	return(p);   
}

struct node *rotate_right(struct node *root)
{
	struct node *p = root->left, *q = root->left->right;

	p->right = root;
	root->left = q;

	root->h = 1 + imax(height(root->left), height(root->right));
	p->h = 1 + imax(height(p->left), height(p->right));

   root->bal = balance_factor(root);
   p->bal = balance_factor(root);   

	return(p);
}

void preorder(struct node *node)
{
   if (node == (struct node *) NULL)
      return;
   printf(" %s", node->key);
   preorder(node->left);
   preorder(node->right);
}

void inorder(struct node *node)
{
   if (node == (struct node *) NULL) 
      return;
   inorder(node->left);
   printf(" %s", node->key);
   inorder(node->right);
}

void postorder(struct node *node)
{
   if (node == (struct node *) NULL)
      return;
   postorder(node->left);
   postorder(node->right);
   printf(" %s", node->key);
}

void report(struct node *root)
{
   printf("pre-order traversal:\t");
   preorder(root);
   printf("\nin-order traversal:\t");
   inorder(root);
   printf("\npost-order traversal:\t");
   postorder(root);
   printf("\nsize = %d height = %d\n", size(root), height(root));
   return;
}

void load(struct node *root, char **arr, int *n)
{
   if (root == (struct node *) NULL)
      return;

   load(root->left, arr, n);
   strcpy(arr[(*n)++], root->key);
   load(root->right, arr, n);
}

void serialize(FILE *fp, struct node *root)
{
   if (root == (struct node *) NULL) {
      fwrite(0, sizeof(char), 1, fp);
      return;
   }
   fwrite(root->key, strlen(root->key)+1, 1, fp);
   serialize(fp, root->left);
   serialize(fp, root->right);
}

struct node *deserialize(FILE *fp, struct node *root)
{
   return(root);
}
