#include <stdlib.h>
#include <stdint.h>
#include "node.h"

int main() {
  int number1 = 3;
  int number2 = 6;

  dObject* data = create_data(1, 0, 0, &number1, sizeof(number1));
  dObject* data2 = create_data(0, 0, 0,&number2, sizeof(number1));

  Node* node = create_node("0x0", data);
  add_data(node, *data2);

  cleanup_node(node);

  return 0;
}