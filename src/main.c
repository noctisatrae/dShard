#include <stdlib.h>
#include <stdint.h>
#include "node.h"

int main() {
  int* number1 = malloc(sizeof(int));
  int* number2 = malloc(sizeof(int));

  *number1 = 3;
  *number2 = 6;

  dObject* data = create_dobject(number1, sizeof(number1));
  dObject* data2 = create_dobject(number2, sizeof(number2));

  Node* node = create_node("0x0", data);
  add_data(node, *data2);

  cleanup_node(node);

  return 0;
}