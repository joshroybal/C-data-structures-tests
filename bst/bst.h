#ifndef BST_H
#define BST_H

struct node {
   char *key;
   struct node *left;
   struct node *right;
};

struct node *create_node(char *);
void dealloc(struct node *);
int size(struct node *);
int height(struct node *);
struct node *search(struct node *, char *);
struct node *minkey(struct node *);
struct node *maxkey(struct node *);
struct node *predecessor(struct node *, struct node *, char *);
struct node *successor(struct node *, struct node *, char *);
void insert(struct node **, char *);
void delete(struct node **, char *);
void preorder(struct node *);
void inorder(struct node *);
void postorder(struct node *);
void report(struct node *);
void serialize(FILE *fp, struct node *);
void deserialize(FILE *fp, struct node **);

#endif
