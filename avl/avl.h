#ifndef AVL_H
#define AVL_H

int imax(int, int);

struct node {
   char *key;
   int h;
   int bal;
   struct node *left;
   struct node *right;
};

struct node *create_node(char *);
void dealloc(struct node *);
int size(struct node *);
int height(struct node *);
int balance_factor(struct node *);
struct node *search(struct node *, char *);
struct node *minkey(struct node *);
struct node *maxkey(struct node *);
struct node *predecessor(struct node *, struct node *, char *);
struct node *successor(struct node *, struct node *, char *);
struct node *insert(struct node *, char *);
struct node *delete(struct node *, char *);
struct node *rotate_left(struct node *);
struct node *rotate_right(struct node *);
void preorder(struct node *);
void inorder(struct node *);
void postorder(struct node *);
void report(struct node *);
void load(struct node *, char **, int *);
void serialize(FILE *fp, struct node *);
struct node *deserialize(FILE *fp, struct node *);

#endif
