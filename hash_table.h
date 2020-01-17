#ifndef CS165_HASH_TABLE // This is a header guard. It prevents the header from being included more than once.
#define CS165_HASH_TABLE  

typedef struct {
// define the components of the hash table here (e.g. the array, bookkeeping for number of elements, etc)
  int size;
  int inserted;
  int tuning;
  struct node **entries;
} hashtable;

typedef struct node {
  int key;
  int value;
  struct node *next;
} node;

typedef int keyType;
typedef int valType;

int allocate(hashtable** ht, int size);
int put(hashtable* ht, keyType key, valType value);
int get(hashtable* ht, keyType key, valType *values, int num_values, int* num_results);
int erase(hashtable* ht, keyType key);
int deallocate(hashtable* ht);
int print(hashtable* ht);

#endif
