#include <stdlib.h>
#include <stdint.h>
#include "node.h"

int main() {
  int* number1 = malloc(sizeof(int));
  int* number2 = malloc(sizeof(int));
  int* number3 = malloc(sizeof(int));

  *number1 = 3;
  *number2 = 6;
  *number3 = 9;

  dObject* data = create_dobject(number1, sizeof(number1));
  dObject* data2 = create_dobject(number2, sizeof(number2));
  dObject* data3 = create_dobject(number3, sizeof(number3));

  Node* node = create_node("0x0", data);
  Node* child_node = create_node("0x01", data3);
  Node* child_node2 = create_node("0x02", malloc(sizeof(char)));
  Node* child_of_node2 = create_node("0x021", malloc(sizeof(char)));

  add_data(node, *data2);

  add_child(node, child_node);
  add_child(node, child_node2);
  add_child(child_node2, child_of_node2);

  recursive_free(node);

  return 0;
}