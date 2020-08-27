#include "common.h"

int boom() {
  int *p = (int *)0x1;
  *p = 0xDEADBEEF;
  return *p;
}
