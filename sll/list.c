#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct node *create_node(char *k, struct node* next)
{
   struct node *node=(struct node *)malloc(sizeof(struct node));
   node->key = (char *) malloc((strlen(k) + 1) * sizeof(char));
   strcpy(node->key, k);
   node->next = next;
   return(node);
}

void destroy_list(struct node *head)
{
	if (head == (struct node *) NULL)
		return;

	destroy_list(head->next);
   free(head->key);
	free(head);
}

struct node *add(struct node *head, char *k)
{
	struct node *node;
	
	if (head == (struct node *) NULL)
      node = create_node(k, (struct node *) NULL);
   else
      node = create_node(k, head);
	return(node);
}

struct node *append(struct node *head, char *k)
{
	if (head == (struct node *) NULL) {
      head = create_node(k, head);
		return(head);
	}
	head->next = append(head->next, k);
   return(head);
}

struct node *insert(struct node *head, char *k)
{
   if (head == (struct node *) NULL || strcmp(k, head->key) < 0) {
      head = create_node(k, head);
      return(head);
   }
   if (strcmp(k, head->key) != 0)
      head->next = insert(head->next, k);
   return(head);
}

struct node *locate(struct node *head, char *k)
{
   if (head == (struct node *) NULL || strcmp(head->key, k) == 0)
		return(head);

	if (head->next != (struct node *) NULL 
         && strcmp(head->next->key, k) == 0)
		return(head);
   return(locate(head->next, k));
}

struct node *delete(struct node *head, char *k)
{
   struct node *target, *tag;

   if (head == (struct node *) NULL)
      return(head);

   if (strcmp(k, head->key) == 0) {
      target = head->next;
      free(head->key);
      free(head);
      return(target);
   }
   target = locate(head, k);
   if (target) {
      tag = target->next;
      target->next = target->next->next;
      free(tag->key);
      free(tag);
   }
   return(head);
}

struct node *reverse(struct node *head)
{
   struct node *body;

   if (head == (struct node *) NULL 
         || head->next == (struct node *) NULL)
      return(head);

   body = reverse(head->next);
   head->next->next = head;
   head->next = (struct node *) NULL;
   return(body);
}

int size(struct node *head)
{
   if (head == (struct node *) NULL)
      return(0);
   return(1 + size(head->next));
}

void print_list(struct node *head)
{
	if (head == (struct node *) NULL) {
		putchar('\n');
		return;
	}
	printf(" %s", head->key);
	print_list(head->next);
}
