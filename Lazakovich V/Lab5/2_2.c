#include "functions2.h"

int main() {
  int **array, n, m = 1;
  input_rows(&n);
  array = memory(n, m);
  input(array, n, &m);
  output(array, n, &m);
  remElement(array, n, &m);
  output(array, n, &m);
  clearMemory(array, n);
  return 0;
}
