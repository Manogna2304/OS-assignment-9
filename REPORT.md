# OS Lab Assignment 9 — Short Report

## Q1: Page-table inspection
The `vmprint()` routine traverses valid user mappings below `KERNBASE`, prints virtual and physical addresses and P/W/U flags, and reports totals. Run `pttest` to inspect the page table before and after reserving and touching four pages.

## Q2: Lazy allocation
Positive `sbrk()` growth reserves virtual space without allocating physical pages immediately. On a valid user page fault, the handler allocates and zeroes a page, maps it with user read/write permissions, and increments the process's fault counter. `faulttest` writes to five distinct reserved pages and checks the fault-count difference; it also checks an invalid access in a child process. Record the exact output from the final local run.

## Q3: FIFO and LRU
`pagerepl` simulates FIFO and LRU page replacement for the specified reference string and compares 3, 4, and 5 frames. With three frames, the expected result for the supplied sequence is 15 FIFO faults and 12 LRU faults. Capture the actual QEMU output for submission.

## Evidence
Add screenshots of the final QEMU output for Q1, Q2, and Q3 to `screenshots/`. Export this report to PDF if required by the course instructions.
