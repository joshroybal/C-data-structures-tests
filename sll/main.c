#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"

#define MAX 38619
#define SIZ 29

int main()
{
   int i, n = 0;
   char str[SIZ];
   char *words[MAX];
   time_t t1, t2;
   struct node *head, *target;

   while (scanf(" %[^\n]", str) != EOF) {
      words[n] = (char *) malloc((strlen(str) + 1) * sizeof(char));
      strcpy(words[n], str);
      ++n;
   }
   
   /* singly linked list recursive insertion test  */
   head = (struct node *) NULL;
   t1 = clock();
   for (i = 0; i < n; ++i)
      head = insert(head, words[i]);
   t2 = clock();
   printf("%f\t", (t2-t1)/(float)CLOCKS_PER_SEC);
   /* singly linked list search test   */
   t1 = clock();
   for (i = 0; i < n; ++i)
      target = locate(head, words[i]);
   t2 = clock();
   printf("%f\t", (t2-t1)/(float)CLOCKS_PER_SEC);
   /* singly linked list deletion test   */
   t1 = clock();
   for (i = 0; i < n; ++i)
      head = delete(head, words[i]);
   t2 = clock();
   printf("%f\n", (t2-t1)/(float)CLOCKS_PER_SEC);

   /* deallocate memory */
   destroy_list(head);
   for (i = 0; i < n; ++i)
      free(words[i]);
   return(0);
}
