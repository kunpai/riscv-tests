#include <stdio.h>
#include "randArr.h"
#include "util.h"

#define ASIZE 16384
#define STEP  16384
#define ITERS   256

int arr[ASIZE];

__attribute__ ((noinline))
int loop(int zero) {
  int t = 0,i,iter;
  for(iter=0; iter < ITERS; ++iter) {
    for(i=0; i < STEP + zero; i+=1) {
      if(randArr[i])  {
        t+=3+3*t;
        arr[i]=t;
      } else {
        t-=1-5*t;
      }
    }
  }
  return arr[zero]+t;
}

int main(int argc, char* argv[]) {
   argc&=10000;
   setStats(1);
   int t=loop(argc); 
   setStats(0);
   volatile int a = t;
}
