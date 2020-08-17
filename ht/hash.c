#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

struct hash_table initialize()
{
   int i;
   struct hash_table t;

   t.n = 2;
   t.k = 0;
   t.buckets = (struct bucket **) malloc(t.n * sizeof(struct bucket *));
   for (i = 0; i < t.n; ++i)
      t.buckets[i] = (struct bucket *) NULL;
   return(t);
}

struct hash_table rebuild(struct hash_table *t)
{
   struct hash_table copy;
   struct bucket *curr;
   int i;

   copy.n = 2 * t->n;
   copy.k = 0;
   copy.buckets = (struct bucket **) malloc(copy.n * sizeof(struct bucket *));
   for (i = 0; i < copy.n; ++i)
      copy.buckets[i] = (struct bucket *) NULL;
   
   for (i = 0; i < t->n; ++i) {
      if (t->buckets[i]) {
         insert(&copy, t->buckets[i]->key);
         curr = t->buckets[i];
         while (curr->next) {
            insert(&copy, curr->next->key);
            curr = curr->next;
         }
      }
   }
   dealloc(t);
   return(copy);
}

struct hash_table shrink(struct hash_table *t)
{
   int i;
   struct hash_table copy;
   struct bucket *curr;

   copy.n = t->n/2;
   copy.k = 0;
   copy.buckets = (struct bucket **) malloc(copy.n * sizeof(struct bucket *));
   for (i = 0; i < copy.n; ++i)
      copy.buckets[i] = (struct bucket *) NULL;
   
   for (i = 0; i < t->n; ++i) {
      if (t->buckets[i]) {
         insert(&copy, t->buckets[i]->key);
         curr = t->buckets[i];
         while (curr->next) {
            insert(&copy, curr->next->key);
            curr = curr->next;
         }
      }
   }
   dealloc(t);
   return(copy);   
}

void dealloc(struct hash_table *t)
{
   int i;
   struct bucket *curr, *tag;

   for (i = 0; i < t->n; ++i) {
      if (t->buckets[i]) {
         curr = t->buckets[i];
         while (curr) {
            tag = curr;
            curr = curr->next;
            free(tag->key);
            free(tag);
         }
      }
   }
   free(t->buckets);
}

unsigned int hash(const char *key)
{
   int i;
   unsigned int h = 0;

   for (i = 0; i < strlen(key); ++i)
      h = h*31+key[i];
   return(h);
}

void insert(struct hash_table *t, const char *k)
{
   unsigned int idx;
   struct bucket *curr;

   if (strlen(search(t, k)))   /* no duplicate keys */
      return;

   if (t->k == t->n)
      *t = rebuild(t);

   idx = hash(k) % t->n;

   if (t->buckets[idx] == (struct bucket *) NULL) {
      t->buckets[idx] = (struct bucket *) malloc(sizeof(struct bucket));
      t->buckets[idx]->key = (char *) malloc(strlen(k)+1);
      strcpy(t->buckets[idx]->key, k);
      t->buckets[idx]->next = (struct bucket *) NULL;
   }
   else {
      curr = t->buckets[idx];
      while (curr->next)
         curr = curr->next;
      curr->next = (struct bucket *) malloc(sizeof(struct bucket));
      curr->next->key = (char *) malloc(strlen(k)+1);
      strcpy(curr->next->key, k);
      curr->next->next = (struct bucket *) NULL;
   }

   ++(t->k);
}

char *search(const struct hash_table *t, const char *k)
{
   struct bucket *curr = t->buckets[hash(k) % t->n];

   while (curr) {
      if (strcmp(curr->key, k) == 0)
         return(curr->key);
      curr = curr->next;
   }
   return("");
}

void update(struct hash_table *t, char *key)
{
}

void delkey(struct hash_table *t, const char *k)
{
   char *target;
   unsigned int idx;
   struct bucket *curr, *tag;

   if (t->k == t->n/4)
      *t = shrink(t);
   
   idx = hash(k) % t->n;
   
   if (t->buckets[idx] == (struct bucket *) NULL)
      return;

   if (strcmp(t->buckets[idx]->key, k) == 0) {
      tag = t->buckets[idx];
      t->buckets[idx] = t->buckets[idx]->next;
      free(tag->key);
      free(tag);
      --(t->k);
      return;
   }

   curr = t->buckets[idx];
   while (curr->next) {
      if (strcmp(curr->next->key, k) == 0) {
         tag = curr->next;
         if (t->buckets[idx] == tag)
            t->buckets[idx] = (struct bucket *) NULL;
         curr->next = curr->next->next;
         free(tag->key);
         free(tag);
         --(t->k);
         return;
      }
      curr = curr->next;
   }
}

int count_collisions(const struct hash_table *t)
{
   int i, n = 0;
   struct bucket *curr;

   for (i = 0; i < t->n; ++i) {
      if (t->buckets[i]) {
         curr = t->buckets[i];
         if (curr->next) {
            /* ++n; */
            curr = curr->next;
            while (curr) {
               ++n;
               curr = curr->next;
            }
         }
      }
   }
   return(n);
}

void print_table(const struct hash_table *t)
{
   int i;
   struct bucket *curr;

   puts("start");
   for (i = 0; i < t->n; ++i) {
      printf(" %d", i);
      curr = t->buckets[i];
      if (curr) {
         printf(" %s", curr->key);
         while (curr->next) {
            printf(" -> %s", curr->next->key);
            curr = curr->next;
         }
      }
      putchar('\n');
   }
   puts("end");
}

void report_ht(const struct hash_table *t)
{
   int i, j;
   float avg, var;
   int *x = (int *) (malloc(t->k * sizeof(int)));
   struct bucket *curr;

   j = 0;
   for (i = 0; i < t->n; ++i) {
      if (t->buckets[i]) {
         x[j] = 0;
         curr = t->buckets[i];
         while (curr) {
            ++(x[j]);
            curr = curr->next;
         }
         ++j;
      }
   }

   avg = 0.;
   for (i = 0; i < j; ++i)
      avg += x[i]/(float)j;

   var = 0.;
   for (i = 0; i < j; ++i)
      var += (x[i]-avg)*(x[i]-avg)/(float)j;

   free(x);
   printf("n = %d k = %d\n", t->n, t->k); 
   printf("no. of collisions = %d\n", count_collisions(t));
   printf("expected = %f\n", .5*t->k*(t->k-1)/(float)t->n);
   printf("load factor = %f\n", j/(float)t->n);
   printf("buckets used = %d\n", j);
   printf("chain length average = %f\n", avg);
   printf("chain length variance = %f\n", var);
}

void write_table(const struct hash_table *t, FILE *fp)
{
   int i;
   struct bucket *curr;

   for (i = 0; i < t->n; ++i) {
      curr = t->buckets[i];
      if (curr) {
         while (curr) {
            fwrite(curr->key, 80, 1, fp);
            curr = curr->next;
         }
      }
   }
}

void read_table(struct hash_table *t, FILE *fp)
{
   char key[80];

   while (!feof(fp)) {
      fread(key, sizeof(key), 1, fp);
      insert(t, key);
   }
}
