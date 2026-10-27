#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  char *p;

  printf(1, "Page table before sbrk:\n");
  vmprint();

  p = sbrk(4 * 4096);
  if(p == (char*)-1){
    printf(1, "sbrk failed\n");
    exit();
  }

  p[0] = 1;
  p[4096] = 1;
  p[8192] = 1;
  p[12288] = 1;

  printf(1, "\nPage table after sbrk(4 * 4096):\n");
  vmprint();

  exit();
}
