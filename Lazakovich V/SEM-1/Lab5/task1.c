#include "array.h"
#include <stdlib.h>

int main() {
  int *array, arraySize, newArraySize;
  arraySize = size(arraySize);
  newArraySize = arraySize * 2;
  array = memory(arraySize);
  choice(array, arraySize);
  newSize(array, newArraySize);
  process(array, arraySize);
  arrayPrint(array, newArraySize);
  free(array);
  return 0;
}
