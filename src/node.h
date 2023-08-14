#ifndef __NODE_H__
#define __NODE_H__

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
  unsigned type:4; 
  unsigned encoding:4;
  unsigned lru_time; // Least Recently used time
  
  // pointer address to the data in RAM
  void* ptr;
} dObject;

typedef struct Link {
  Node* from;
  Node* to;
} Link;

Node* create_node(char* id, dObject* data);
dObject* create_data(
  unsigned type, 
  unsigned encoding, 
  unsigned lru_time, 
  void* data_ptr
);
Node* add_child(Node* parent, Node* child);
void* add_data(Node* node, dObject* new_ptr);
void increase_refcount(Node* node);
void decrease_refcount(Node* node);
void cleanup_root(Node* node);

#endif