#include <stdio.h>
#include "util.h"

#define ASIZE  8192
#define STEP    128
#define ITERS   100

float arrA[ASIZE];
float arrB[ASIZE];

__attribute__ ((noinline))
float loop(int zero) {
  int i, iters;
  float t1;

  for(iters=zero; iters < ITERS; iters+=1) {
    for(i=zero; i < ASIZE; i+=1) {
      arrA[i]=arrA[i]*3.2f + arrB[i];
    }
    t1+=arrA[ASIZE-1];
  }

  return t1;
}

int main(int argc, char* argv[]) {
   argc&=10000;
   setStats(1);
   int t=loop(argc); 
   setStats(0);
   volatile float a = t;
}