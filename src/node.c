#include <stdlib.h>
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

void cleanup_root(Node* node)
{
  free(node->relationships);
  free(node->data->ptr);
  free(node->data);
  free(node);
}

/*
int main() {
  // Create a dObject for the root node
  dObject* rootData = (dObject*)malloc(sizeof(dObject));
  rootData->type = 0;
  rootData->encoding = 0;
  rootData->lru_time = 0;
  rootData->ptr = NULL; // Assuming no data for the root node

  // Create the root node
  Node* rootNode = create_node("0x0", rootData);

  // Create a dObject for a child node
  dObject* childData = (dObject*)malloc(sizeof(dObject));
  childData->type = 1;
  childData->encoding = 1;
  childData->lru_time = 0;
  childData->ptr = NULL; // Assuming no data for the child node

  // Create the child node
  Node* childNode = create_node("0x01", childData);

  // Add the child node to the root node
  add_child(rootNode, childNode);

  // Increase the reference count of the child node
  increase_refcount(childNode);

  // Decrease the reference count of the child node
  decrease_refcount(childNode);

  cleanup_root(rootNode);

  return 0;
}
*/