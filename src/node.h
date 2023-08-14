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
  void *ptr;
} dObject;

typedef struct Link {
  Node* from;
  Node* to;
} Link;

Node* create_node(char* id, dObject* data);
Node* add_child(Node* parent, Node* child);
void increase_refcount(Node* node);
void decrease_refcount(Node* node);
void cleanup_root(Node* node);

#endif