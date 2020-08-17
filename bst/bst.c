#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

struct node *create_node(char *k)
{
   struct node *node = (struct node *) malloc(sizeof(struct node));
   node->key = (char *) malloc((strlen(k) + 1) * sizeof(char));
   strcpy(node->key, k);
   node->left = (struct node *) NULL;
   node->right = (struct node *) NULL;
   return(node);
}

void dealloc(struct node *node)
{
   if (node == (struct node *) NULL)
      return;
   dealloc(node->left);
   dealloc(node->right);
   free(node->key);
   free(node);
}

int size(struct node *node)
{
   if (node == (struct node *) NULL)
      return(0);
   else
      return(1 + size(node->left) + size(node->right));
}

int height(struct node *node)
{
   int hl, hr;

   if (node == (struct node *) NULL)
      return(-1);
   hl = height(node->left);
   hr = height(node->right);
   return((hl > hr) ? 1+hl : 1+hr);   
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

void insert(struct node **node, char *k)
{
   if (*node == (struct node *) NULL) {
      *node = create_node(k);
      return;
   }
   if (strcmp(k, (*node)->key) < 0)
      insert(&(*node)->left, k);
   else if (strcmp(k, (*node)->key) > 0)
      insert(&(*node)->right, k);
   else
      return;
}

void delete(struct node **root, char *k)
{
   struct node *tag;

   if (*root == (struct node *) NULL) 
      return;

   if (strcmp(k, (*root)->key) < 0)
      delete(&(*root)->left, k);
   else if (strcmp(k, (*root)->key) > 0)
      delete(&(*root)->right, k);
   else {
      if ((*root)->left == (struct node *) NULL) {
         tag = (*root)->right;
         free((*root)->key);
         free(*root);
         *root = tag;
         return;
      }
      else if ((*root)->right == (struct node *) NULL) {
         tag = (*root)->left;
         free((*root)->key);
         free(*root);
         *root = tag;
         return;
      }
      tag = maxkey((*root)->left);
      free((*root)->key);
      (*root)->key = (char *) malloc((strlen(tag->key)+1)*sizeof(char));
      strcpy((*root)->key, tag->key);
      delete(&(*root)->left, tag->key);
   }   
}

void preorder(struct node *root)
{
   if (root == (struct node *) NULL)
      return;
   printf(" %s", root->key);
   preorder(root->left);
   preorder(root->right);
}

void inorder(struct node *root)
{
   if (root == (struct node *) NULL) 
      return;
   inorder(root->left);
   printf(" %s", root->key);
   inorder(root->right);
}

void postorder(struct node *root)
{
   if (root == (struct node *) NULL)
      return;
   postorder(root->left);
   postorder(root->right);
   printf(" %s", root->key);
}

void report(struct node *root)
{
   /*
   printf("pre-order traversal:\t");
   preorder(root);
   printf("\nin-order traversal:\t");
   inorder(root);
   printf("\npost-order traversal:\t");
   postorder(root);
   */
   printf("size = %d height = %d\n", size(root), height(root));
   return;
}

void serialize(FILE *fp, struct node *root)
{   
   if (root == (struct node *) NULL) {
      fprintf(fp, "\n");
      return;
   }
   fprintf(fp, "%s\n", root->key);
   serialize(fp, root->left);
   serialize(fp, root->right);
}

void deserialize(FILE *fp, struct node **root)
{
   char key[80];

   if (fscanf(fp, " %[^\n]", key) == EOF || strcmp(key, "") == 0)
      return;
   *root = create_node(key);
   deserialize(fp, &(*root)->left);
   deserialize(fp, &(*root)->right);
}
