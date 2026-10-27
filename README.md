# OS Lab Assignment 9

## Environment
- xv6-public (x86)
- Ubuntu on WSL2
- GCC, Make, QEMU

## Assignment 9

### Q1: Page Table Inspection
Implemented vmprint() to display valid user page mappings and test allocation using pttest.

### Q2: Lazy Allocation
Modified sbrk() to reserve virtual memory lazily, added page-fault handling, and implemented getfaults().
Test program: faulttest.c

### Q3: Page Replacement
Implemented FIFO and LRU simulations for a reference string using 3, 4, and 5 frames.
Test program: pagerepl.c

## Build
Run:
    make clean
    make

## Run
Run:
    make qemu-nox

At the xv6 shell:
    pttest
    faulttest
    pagerepl
