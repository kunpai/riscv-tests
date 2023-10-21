#include <stdio.h>
#include <stdlib.h>     /* malloc, free, rand */

#include "util.h"

#define ASIZE  65536
#define STEP     128
#define ITERS  3276800
#define LEN     2048


typedef struct dude {
  int p1,p2,p3,p4;
} dude;


dude arr[ASIZE];
__attribute__ ((noinline))
int loop(int zero) {
  int t = 0, count=0;

  unsigned lfsr = 0xACE1u;
  do
  {
      count++;
      /* taps: 16 14 13 11; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1 */
      lfsr = (lfsr >> 1) ^ (-(lfsr & 1u) & 0xB400u);    

      t+=arr[lfsr].p1 + arr[lfsr].p2 + arr[lfsr].p3;

      //lfsr = lfsr + arr[lfsr].p1;

  } while(++count < ITERS);
  //} while(lfsr != 0xACE1u);

  return t;
}


int main(int argc, char* argv[]) {
   argc&=10000;
   setStats(1);
   int t=loop(argc); 
   setStats(0);
   volatile int a = t;
}
