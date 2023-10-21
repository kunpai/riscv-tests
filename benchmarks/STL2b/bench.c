#include <stdio.h>
#include "util.h"

#define ASIZE 131072
#define STEP     512
#define ITERS    256

int arr[ASIZE];

__attribute__ ((noinline))
int loop(int zero) {
  int t = 0,i,iter;
  for(iter=0; iter < ITERS; ++iter) {
    for(i=iter; i < ASIZE; i+=STEP) {
      arr[i]=i;
    }
    t+=arr[zero];
  }
  return t+arr[zero];
}

int main(int argc, char* argv[]) {
   argc&=10000;
   setStats(1);
   int t=loop(argc); 
   setStats(0);
   volatile int a = t;
}