#ifndef DLL_H
#define DLL_H

struct node {
   char *key;
   struct node *prev;
   struct node *next;
};

struct node *create_node(char *, struct node *, struct node *);
void destory_list(struct node *);
void insert(struct node **, struct node **, char *);
struct node *search(struct node *, char *);
void delete(struct node **, struct node **, char *);
void reverse(struct node **, struct node **);
void print(struct node *);

#endif
