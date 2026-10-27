#include "types.h"
#include "stat.h"
#include "user.h"

#define N 20

static int refs[N] = {
  7, 0, 1, 2, 0, 3, 0, 4, 2, 3,
  0, 3, 2, 1, 2, 0, 1, 7, 0, 1
};

static int
simulate(int capacity, int lru)
{
  int frames[5], loaded[5], last[5];
  int i, j, victim, faults = 0, hit;

  for(j = 0; j < capacity; j++){
    frames[j] = -1;
    loaded[j] = -1;
    last[j] = -1;
  }

  for(i = 0; i < N; i++){
    hit = 0;
    for(j = 0; j < capacity; j++){
      if(frames[j] == refs[i]){
        hit = 1;
        last[j] = i;
        break;
      }
    }

    if(hit)
      continue;

    faults++;
    victim = -1;

    for(j = 0; j < capacity; j++){
      if(frames[j] == -1){
        victim = j;
        break;
      }
    }

    if(victim == -1){
      victim = 0;
      for(j = 1; j < capacity; j++){
        if(lru && last[j] < last[victim])
          victim = j;
        if(!lru && loaded[j] < loaded[victim])
          victim = j;
      }
    }

    frames[victim] = refs[i];
    loaded[victim] = i;
    last[victim] = i;
  }

  return faults;
}

int
main(void)
{
  int n, fifo, lru;

  printf(1, "Reference string: 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1\n");

  for(n = 3; n <= 5; n++){
    fifo = simulate(n, 0);
    lru = simulate(n, 1);

    printf(1, "\nFrames: %d\n", n);
    printf(1, "FIFO page faults: %d\n", fifo);
    printf(1, "FIFO hits: %d, hit ratio: %d%%\n",
           N - fifo, (N - fifo) * 100 / N);
    printf(1, "LRU page faults: %d\n", lru);
    printf(1, "LRU hits: %d, hit ratio: %d%%\n",
           N - lru, (N - lru) * 100 / N);
  }

  exit();
}
