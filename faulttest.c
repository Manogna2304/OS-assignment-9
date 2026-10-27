#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  char *p;
  int pages[5] = {0, 3, 7, 15, 31};
  int i, before, after;

  p = sbrk(32 * 4096);
  if(p == (char*)-1){
    printf(1, "sbrk failed\n");
    exit();
  }

  printf(1, "Reserved 32 pages of virtual memory\n");

  // Establish the baseline after initial output.
  before = getfaults();

  for(i = 0; i < 5; i++)
    p[pages[i] * 4096] = i + 1;

  after = getfaults();

  printf(1, "Pages touched: 5\n");
  printf(1, "Additional faults from page writes: %d\n",
         after - before);

  if(after - before == 5)
    printf(1, "PASS: lazy allocation test\n");
  else
    printf(1, "FAIL: unexpected fault count\n");

  exit();
}
