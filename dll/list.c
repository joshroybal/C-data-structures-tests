#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct node *create_node(char *key, struct node *prev, struct node *next)
{
   struct node *node = (struct node *) malloc(sizeof(struct node));
   node->key = (char *) malloc((strlen(key) + 1) * sizeof(char));
   strcpy(node->key, key);
   node->prev = prev;
   node->next = next;
   return(node);
}

void destroy_list(struct node *head)
{
   struct node *tag;

   if (!head)
      return;

   while (head) {
      tag = head;
      head = head->next;
      free(tag->key);
      free(tag);
   }
}

void insert(struct node **head, struct node **tail, char *k)
{
   struct node *curr, *newnode;

   if (!(*head) && !(*tail)) {   /* empty list */
      *head = create_node(k, 0, 0);
      *tail = *head;
      return;
   }

   if (strcmp(k, (*head)->key) < 0) {  /* new head node */
      newnode = create_node(k, 0, *head);
      (*head)->prev = newnode;
      *head = newnode;
      return;
   }

   /* find insertion location */
   curr = *head;
   while (curr->next && strcmp(k, curr->next->key) > 0)
      curr = curr->next;

   /* no duplicate keys */
   if (strcmp(k, curr->key) == 0 
         || (curr->next && strcmp(k, curr->next->key) == 0))
      return;

   newnode = create_node(k, 0, 0);
   if (curr->next) { /* insert in body of list */
      newnode->prev = curr;
      newnode->next = curr->next;
      curr->next->prev = newnode;
      curr->next = newnode;
   }
   else {   /* new tail node */
      newnode->prev = curr;
      newnode->next = (struct node *) NULL;
      curr->next = newnode;
      *tail = newnode;
   }
}

struct node *search(struct node *node, char *k)
{
   while (node && strcmp(node->key, k) != 0)
      node = node->next;

   return(node);
}

void delete(struct node **head, struct node **tail, char *k)
{
   struct node *target = search(*head, k);

   if (target) {
      if (target->prev)
         target->prev->next = target->next;
      if (target->next)
         target->next->prev = target->prev;
      if (target == *head)
         *head = target->next;
      if (target == *tail)
         *tail = target->prev;
      free(target->key);
      free(target);
   }
}

void reverse(struct node **head, struct node **tail)
{
   struct node *tmp, *curr = *head;

   if (!(*head) && !(*tail))
      return;

   while (curr) {
      tmp = curr->prev;
      curr->prev = curr->next;
      curr->next = tmp;
      curr = curr->prev;
   }
   if (tmp) {
      *tail = *head;
      *head = tmp->prev;
   }
}

void print_list(struct node *node)
{
   while (node) {
      printf(" %s", node->key);
      node = node->next;
   }
   putchar('\n');
}

