#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"

#define MAX 38619
#define SIZ 29

int main()
{
   int i, n = 0;
   char str[SIZ];
   char *target;
   char *words[MAX];
   time_t t1, t2;
   struct hash_table *table;

   while (scanf(" %[^\n]", str) != EOF) {
      words[n] = (char *) malloc((strlen(str) + 1) * sizeof(char));
      strcpy(words[n++], str);
   }

   /* hash table insertion test   */
   table = (struct hash_table *) malloc(sizeof(struct hash_table));
   *table = initialize();

   t1 = clock();
   for (i = 0; i < n; ++i)
      insert(table, words[i]);
   t2 = clock();
   printf("%f\t", (t2-t1)/(float)CLOCKS_PER_SEC);
   /* hash table search test */
   t1 = clock();
   for (i = 0; i < n; ++i)
      target = search(table, words[i]);
   t2 = clock();
   printf("%f\t", (t2-t1)/(float)CLOCKS_PER_SEC);
   /* hash table deletion test */
   t1 = clock();
   for (i = 0; i < n; ++i)
      delkey(table, words[i]);
   t2 = clock();
   printf("%f\n", (t2-t1)/(float)CLOCKS_PER_SEC);

   dealloc(table);
   free(table);
   
   /* deallocate memory */
   for (i = 0; i < n; ++i)
      free(words[i]);
   return(0);
}
