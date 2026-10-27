# OS Lab Assignment 9 — xv6 x86

**Repository:** [Manogna2304/OS-assignment-9](https://github.com/Manogna2304/OS-assignment-9)  
**Base OS:** MIT xv6-public (x86)  
**Languages:** C and x86 Assembly  
**Development environment:** Ubuntu on WSL2, GCC, GNU Make, and QEMU

## 1. Project Overview

This project implements three operating-system concepts using xv6-public:

1. **Page-Table Inspection:** Display valid user virtual-to-physical mappings, page flags, and page-table statistics.
2. **Lazy Memory Allocation:** Reserve virtual memory first and allocate physical pages only when they are accessed.
3. **Page Replacement Algorithms:** Simulate FIFO and LRU page replacement and compare their page-fault counts.

The repository contains kernel source files, user programs, test programs, and a report draft.

## 2. Repository Structure

```text
OS-assignment-9/
├── kernel/
│   ├── proc.c
│   ├── proc.h
│   ├── syscall.c
│   ├── syscall.h
│   ├── sysproc.c
│   ├── trap.c
│   ├── vm.c
│   └── ...other kernel files and headers
├── user/
│   ├── pttest.c
│   ├── faulttest.c
│   ├── pagerepl.c
│   ├── user.h
│   ├── usys.S
│   └── ...other user programs and support files
├── screenshots/
│   └── README.md
├── REPORT.md
└── README.md
```

**Note:** Upstream xv6-public uses a mostly flat source layout. The reorganized folders are for easier browsing; their build configuration and assignment-specific changes must be verified before treating this layout as a standalone buildable project.

## 3. Question 1 — Page-Table Inspection

### Objective

Inspect the current process's page table and display its valid user mappings.

### Implementation

The `vmprint()` routine traverses the current process's virtual address space below `KERNBASE`. For each valid user mapping, it displays:

- Virtual address
- Corresponding physical address
- Page flags: Present (P), Writable (W), and User-accessible (U)

It also prints the total number of valid user pages and the number of page-table pages represented by the user mappings.

A system-call interface allows a user program to invoke the kernel routine.

### Test program

Run:

```text
pttest
```

The test prints the page table before and after requesting four pages using `sbrk(4 * 4096)` and touching those pages.

### Expected result

The number of valid user mappings should increase by four after the four new pages have been allocated and touched, assuming no unrelated address-space changes occur between the two listings.

Save a screenshot showing both page-table listings.

## 4. Question 2 — Lazy Memory Allocation

### Objective

Delay physical memory allocation until a process accesses a reserved virtual page.

### Implementation

- Positive `sbrk(n)` increases the process's recorded size without immediately allocating every physical page.
- A page fault occurs when the process accesses a reserved but unmapped page.
- The page-fault handler checks whether the address belongs to the process's valid address space.
- The faulting address is rounded down to the page boundary.
- A physical page is allocated and initialized to zero.
- The page is mapped with user read/write permissions.
- The process's handled-fault counter is incremented after successful allocation.
- Invalid accesses cause the faulting process to be marked for termination.
- `copyuvm()` skips reserved pages that do not yet have physical mappings.
- Deallocation handles absent pages without assuming every reserved page has physical memory.

The `getfaults()` system call returns the current process's handled lazy-page-fault count.

### Test program

Run:

```text
faulttest
```

The test reserves 32 pages and writes to five distinct page indices:

```text
0, 3, 7, 15, 31
```

It measures the fault-count difference around those writes. It also tests an invalid address in a child process.

### Expected result

The five deliberate page writes should cause **five additional lazy-allocation faults**.

The invalid access should terminate the child process while allowing the parent to continue. The absolute fault count may already be nonzero before the
