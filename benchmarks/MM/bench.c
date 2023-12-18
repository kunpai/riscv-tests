#include <stdio.h>
#include "util.h"

#define ASIZE 2048
#define STEP   128
#define ITERS  2
#define LEN    32768

int arr[ASIZE];

struct ll {
  int val;
  struct ll* _next;
};

// Pre-allocate an array of nodes
struct ll nodes[LEN + 1];

__attribute__ ((noinline))
int loop(int zero, struct ll* n) {
  int t = 0, i, iter;
  for(iter = 0; iter < ITERS; ++iter) {
    struct ll* cur = n;
    while(cur != NULL) {
      t += cur->val;
      cur = cur->_next;
    }
  }
  return t;
}

int main(int argc, char* argv[]) {
  argc &= 10000;
  struct ll* n = nodes;
  struct ll* cur = n;

  int i;
  for (i = 0; i < LEN; ++i) {
    cur->val = i;
    cur->_next = cur + 1; // Point to the next element in the array
    cur = cur->_next;
  }
  cur->val = 100;
  cur->_next = NULL;

  setStats(1);
  int t = loop(argc, n);
  setStats(0);

  volatile int a = t;
}
