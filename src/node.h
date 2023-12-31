#ifndef __NODE_H__
#define __NODE_H__

#include <stddef.h>
typedef struct Node {
    char* id; // Unique identifier for the node (e.g root node 0x0)
    struct dObject* data;
    struct Link** relationships;
    struct Node** children; // Pointer to an array of child nodes
    int num_children;
    // refCount for garbage collection
    int refcount;
} Node;

typedef struct dObject {
  // pointer address to the data in RAM
  void* ptr;
  size_t data_size;
} dObject;

typedef struct Link {
  Node* from;
  Node* to;
} Link;

Node* create_node(char* id, dObject* data);
dObject* create_dobject(
  void* data_ptr,
  size_t data_size
);
Node* add_child(Node* parent, Node* child);
void add_data(Node* node, dObject new_data);
void increase_refcount(Node* node);
void decrease_refcount(Node* node);
void recursive_free(Node* node);

#endif