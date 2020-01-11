#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>


#include "hash_table.h"

// This is where you can implement your own tests for the hash table
// implementation. 
int main(void) {

  hashtable *ht = NULL;
  int size = 10;
  allocate(&ht, size);
  
  int key = 0;
  int value = -1;

  put(ht, key, value);
  put(ht, 0, 2);
  put(ht, 1, -2);
  
  printf("Showing what is currently in the hashtable\n");
  for(int i = 0; i < size -1; ++i){
    node *temp = ht->entries[i];
    if(temp != NULL){
      printf("slot: %d, key: %d, value: %d\n",i,temp->key,temp->value);
      while(temp->next != NULL){
        temp = temp->next;
        printf("slot: %d, key: %d, value: %d\n",i,temp->key,temp->value);
      }
    }
    else{
      printf("slot: %d is empty\n", i);
    }
  }

  
  int num_values = 1;

  valType* values = malloc(1 * sizeof(valType));

  int* num_results = NULL;

  get(ht, key, values, num_values, num_results);
  printf("num_results: %d\n", (*num_results));
  if ((*num_results) > num_values) {
    values = realloc(values, (*num_results) * sizeof(valType));
    get(ht, 0, values, num_values, num_results);
  }

  for (int i = 0; i < (*num_results); i++) {
    printf("value of %d is %d \n", i, values[i]);
  }
  free(values);
  
  erase(ht, 0);

  deallocate(ht);
  
  return 0;
}
