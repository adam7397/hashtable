#include "hash_table.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


// Initialize the components of a hashtable.
// The size parameter is the expected number of elements to be inserted.
// This method returns an error code, 0 for success and -1 otherwise (e.g., if the parameter passed to the method is not null, if malloc fails, etc).
int allocate(hashtable** ht, int size) {

  // Check the size of the paramter passed in, if it is too small initialize nothing
  if (size < 1 ) {
    return -1;
  }
  
  if(((*ht) = malloc(sizeof(hashtable))) == NULL){
    return -1;
  }

  // Once we have confirmed the size, we need to create the array by allocating memory
  // Pass the pointer of the array back so that the program can access it or something
  if(((*ht)->entries = malloc(sizeof(node*) * size)) == NULL){
    return -1;
  }
  (*ht)->size = size;
  (*ht)->inserted = 0;
  (*ht)->tuning = 0;
  
  // Set the entires to point to null
  for(int i = 0; i < size; ++i){
    (*ht)->entries[i] = NULL;
  }
  return 0;
}

// This method inserts a key-value pair into the hash table.
// It returns an error code, 0 for success and -1 otherwise (e.g., if malloc is called and fails).
int put(hashtable* ht, keyType key, valType value) {
    // Use our hash function here to determine which index the value should be placed
    int slot = key % ht->size;

    // Create a new node for the value
    struct node *newNode = malloc(sizeof(struct node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    // Checking here for if there is anything in the index yet
    if (ht->entries[slot] == NULL){
      ht->entries[slot] = newNode;
    }
    // If there is, we will need to traverse the linked list to update the teminal node next pointer
    else {
      node *endNode = ht->entries[slot];
      while(endNode->next != NULL){
        endNode = endNode->next;
      }

      endNode->next = newNode;
    }

    return 0;
}

// This method retrieves entries with a matching key and stores the corresponding values in the
// values array. The size of the values array is given by the parameter
// num_values. If there are more matching entries than num_values, they are not
// stored in the values array to avoid a buffer overflow. The function returns
// the number of matching entries using the num_results pointer. If the value of num_results is greater than
// num_values, the caller can invoke this function again (with a larger buffer)
// to get values that it missed during the first call. 
// This method returns an error code, 0 for success and -1 otherwise (e.g., if the hashtable is not allocated).
int get(hashtable* ht, keyType key, valType *values, int num_values, int* num_results) {
  int slot = key % sizeof(ht);
  
  struct node *entry = ht->entries[slot];

  if(entry == NULL){
    printf("There are no matching hashed keys");
    return -1;
  }

  // Allocate the num_results, as just a NULL pointer was passed  
  if((num_results = malloc(sizeof(int))) == NULL){
    return -1;
  }
  // Start it at 0 so that it cxan be incremented as we check
  (*num_results) = 0;
  
   
  //int* num_results = 0;
  printf("num_results: %d\n", (*num_results));

  int temp = num_values;
  while(entry != NULL){
    if(entry->key == key){
      ++(*num_results);
      if(temp != 0){
        values[num_values-temp] = entry->value;
        --temp;
      }
    }
    entry = entry->next;
  }
  printf("num_results: %d\n", (*num_results));

  return 0;
}

// This method erases all key-value pairs with a given key from the hash table.
// It returns an error code, 0 for success and -1 otherwise (e.g., if the hashtable is not allocated).
int erase(hashtable* ht, keyType key) {
    int slot = key % sizeof(ht);

    if (ht->entries [slot] == NULL) {
      return -1;
    }
    else {
      struct node *firstNode = ht->entries[slot];
      struct node *secondNode = firstNode->next;
      while(secondNode->next != NULL){
        if (secondNode->key == key) {
          firstNode->next = secondNode->next;
          // Deallocate the secondNode here somehow
          free(secondNode);
          secondNode = firstNode->next->next;
        }
      }
    }
    return 0;
}

// This method frees all memory occupied by the hash table.
// It returns an error code, 0 for success and -1 otherwise.
int deallocate(hashtable* ht) {
    // This line tells the compiler that we know we haven't used the variable
    // yet so don't issue a warning. You should remove this line once you use
    // the parameter.
    (void) ht;
    free(ht);
    return 0;
}
