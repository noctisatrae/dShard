#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

Node* create_node(char* id, dObject* data)
{ 
  Node* new_node = (Node*)malloc(sizeof(Node));
  new_node->id = id;
  new_node->children = NULL;
  new_node->relationships = NULL;
  new_node->data = data;
  new_node->num_children = 0;

  return new_node;
}

// create a dObject without any node attached to it.
dObject* create_data(
  unsigned type, 
  unsigned encoding, 
  unsigned lru_time,
  void* data_ptr,
  size_t data_size
)
{
  // two object of 4 bytes in the struct so struct size + 8???
  dObject* new_d_object = (dObject*)malloc(sizeof(dObject));

  if(new_d_object == NULL) {
      fprintf(stderr, "Failed to allocate memory for dObject.");
      exit(1);
  }

  new_d_object->type = type;
  new_d_object->encoding = encoding; 
  new_d_object->lru_time = lru_time;
  new_d_object->ptr = malloc(data_size);

  if(new_d_object->ptr == NULL) {
      fprintf(stderr, "Failed to allocate memory for dObject data.");
      exit(1);
  }

  memcpy(new_d_object->ptr, data_ptr, data_size); 

  return new_d_object;  
}

/*

Add data to a node and if there was already data, delete it and free memory, then replace.

*/
void add_data(Node* node, dObject new_data)
{
  free(node->data->ptr);
  free(node->data);

  node->refcount += 1;

  node->data = (dObject*)malloc(sizeof(dObject));
  if (node->data == NULL)
  {
    fprintf(stderr, "Failed to allocate memory for node data.");
    exit(1);
  }

  node->data->ptr = malloc(new_data.data_size);
  if (node->data->ptr == NULL)
  {
    fprintf(stderr, "Failed to allocate memory for node data pointer.");
    exit(1);
  }

  // memcpy(node->data->ptr, new_data.ptr, new_data.data_size);
  node->data->ptr = new_data.ptr;
  node->data->data_size = new_data.data_size;

  node->data->lru_time = new_data.lru_time;
  node->data->encoding = new_data.encoding;
  node->data->type = new_data.type;
}

Node* add_child(Node* parent, Node* child)
{ 
  parent->num_children += 1;
  parent->refcount += 1;
  parent->children = realloc(parent->children, parent->num_children * sizeof(Node*));
  parent->children[parent->num_children - 1] = child;

  return child;
}

void increase_refcount(Node* node) 
{
  node->refcount += 1;
}

void decrease_refcount(Node* node) 
{
  node->refcount -= 1;
  if (node->refcount == 0)
  {
    free(node->relationships);
    free(node->data->ptr);
    free(node->data);
    free(node);
  }
}

void cleanup_node(Node* node)
{
  free(node->relationships);
  free(node->children);
  free(node->data->ptr);
  free(node->data);
  free(node);
}