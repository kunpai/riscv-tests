#include <stdio.h>
#include "util.h"

#define ASIZE  8096
#define STEP    128
#define ITERS   170

double arrA[ASIZE];
double arrB[ASIZE];

__attribute__ ((noinline)) 
double loop(int zero) {
  int i, iters;
  double t1;

  for(iters=zero; iters < ITERS; iters+=1) {
    for(i=zero; i < ASIZE; i+=1) {
      arrA[i]=arrA[i]*3.2 + arrB[i];
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
   volatile double a = t;
}