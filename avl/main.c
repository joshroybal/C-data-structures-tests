#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "avl.h"

#define MAX 38619
#define SIZ 29

int main()
{
   int i, n = 0;
   char str[SIZ];
   char *words[MAX];
   time_t t1, t2;
   struct node *root, *target;

   while (scanf(" %[^\n]", str) != EOF) {
      words[n] = (char *) malloc((strlen(str) + 1) * sizeof(char));
      strcpy(words[n++], str);
   }
   
   /* binary search tree insertion test   */
   root = (struct node *) NULL;
   t1 = clock();
   for (i = 0; i < n; ++i)
      root = insert(root, words[i]);
   t2 = clock();
   printf("%f\t", (t2-t1)/(float)CLOCKS_PER_SEC);
   /* binary search tree search test */
   t1 = clock();
   for (i = 0; i < n; ++i)
      target = search(root, words[i]);
   t2 = clock();
   printf("%f\t", (t2-t1)/(float)CLOCKS_PER_SEC);
   /* binary search tree deletion test */
   t1 = clock();
   for (i = 0; i < n; ++i)
      root = delete(root, words[i]);
   t2 = clock();
   printf("%f\n", (t2-t1)/(float)CLOCKS_PER_SEC);

   dealloc(root);   

   /* deallocate memory */
   for (i = 0; i < n; ++i)
      free(words[i]);
   return(0);
}
