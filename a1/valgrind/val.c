#include <stdlib.h>
#include <stdio.h>

int main() {
    int* as;
    as = malloc(10 * sizeof(int));
    int sum = 0;

    for (int i = 0; i < 10; ++i) {
        as[i] = i;
    }

    for (int i = 0; i < 10; ++i) {
        sum += as[i];
    }

    printf("%d\n", sum);

    free(as);
    free(as);
}

// -------- Valgrind output ---------
//
// Original code:
// ==6429== Memcheck, a memory error detector
// ==6429== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
// ==6429== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
// ==6429== Command: ./a.out
// ==6429==
// 45
// ==6429==
// ==6429== HEAP SUMMARY:
// ==6429==     in use at exit: 0 bytes in 0 blocks
// ==6429==   total heap usage: 2 allocs, 2 frees, 1,064 bytes allocated
// ==6429==
// ==6429== All heap blocks were freed -- no leaks are possible
// ==6429==
// ==6429== For lists of detected and suppressed errors, rerun with: -s
// ==6429== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0
//
//
// No initialization
// ==6559== Memcheck, a memory error detector
// ==6559== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
// ==6559== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
// ==6559== Command: ./a.out
// ==6559==
// ==6559== Use of uninitialised value of size 8
// ==6559==    at 0x109178: main (val.c:10)
// ==6559==
// ==6559== Use of uninitialised value of size 8
// ==6559==    at 0x1091A1: main (val.c:14)
// ==6559==
// 45
// ==6559== Conditional jump or move depends on uninitialised value(s)
// ==6559==    at 0x48440E5: free (vg_replace_malloc.c:974)
// ==6559==    by 0x1091D4: main (val.c:19)
// ==6559==
// ==6559== Invalid free() / delete / delete[] / realloc()
// ==6559==    at 0x484412F: free (vg_replace_malloc.c:974)
// ==6559==    by 0x1091D4: main (val.c:19)
// ==6559==  Address 0x4033ab0 is 2736 bytes inside data symbol "_rtld_local"
// ==6559==
// ==6559== Invalid read of size 8
// ==6559==    at 0x4004E89: _dl_fini (dl-fini.c:75)
// ==6559==    by 0x48CECC5: __run_exit_handlers (exit.c:111)
// ==6559==    by 0x48CEE0F: exit (exit.c:141)
// ==6559==    by 0x48B5CD6: (below main) (libc_start_call_main.h:74)
// ==6559==  Address 0x70000002e is not stack'd, malloc'd or (recently) free'd
// ==6559==
// ==6559==
// ==6559== Process terminating with default action of signal 11 (SIGSEGV): dumping core
// ==6559==  Access not within mapped region at address 0x70000002E
// ==6559==    at 0x4004E89: _dl_fini (dl-fini.c:75)
// ==6559==    by 0x48CECC5: __run_exit_handlers (exit.c:111)
// ==6559==    by 0x48CEE0F: exit (exit.c:141)
// ==6559==    by 0x48B5CD6: (below main) (libc_start_call_main.h:74)
// ==6559==  If you believe this happened as a result of a stack
// ==6559==  overflow in your program's main thread (unlikely but
// ==6559==  possible), you can try to increase the size of the
// ==6559==  main thread stack using the --main-stacksize= flag.
// ==6559==  The main thread stack size used in this run was 8388608.
// ==6559==
// ==6559== HEAP SUMMARY:
// ==6559==     in use at exit: 1,024 bytes in 1 blocks
// ==6559==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
// ==6559==
// ==6559== LEAK SUMMARY:
// ==6559==    definitely lost: 0 bytes in 0 blocks
// ==6559==    indirectly lost: 0 bytes in 0 blocks
// ==6559==      possibly lost: 0 bytes in 0 blocks
// ==6559==    still reachable: 1,024 bytes in 1 blocks
// ==6559==         suppressed: 0 bytes in 0 blocks
// ==6559== Rerun with --leak-check=full to see details of leaked memory
// ==6559==
// ==6559== Use --track-origins=yes to see where uninitialised values come from
// ==6559== For lists of detected and suppressed errors, rerun with: -s
// ==6559== ERROR SUMMARY: 23 errors from 5 contexts (suppressed: 0 from 0)
// [1]    6559 segmentation fault (core dumped)  valgrind ./a.ou
//
//
// No free:
// ==6664== Memcheck, a memory error detector
// ==6664== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
// ==6664== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
// ==6664== Command: ./a.out
// ==6664==
// 45
// ==6664==
// ==6664== HEAP SUMMARY:
// ==6664==     in use at exit: 40 bytes in 1 blocks
// ==6664==   total heap usage: 2 allocs, 1 frees, 1,064 bytes allocated
// ==6664==
// ==6664== LEAK SUMMARY:
// ==6664==    definitely lost: 40 bytes in 1 blocks
// ==6664==    indirectly lost: 0 bytes in 0 blocks
// ==6664==      possibly lost: 0 bytes in 0 blocks
// ==6664==    still reachable: 0 bytes in 0 blocks
// ==6664==         suppressed: 0 bytes in 0 blocks
// ==6664== Rerun with --leak-check=full to see details of leaked memory
// ==6664==
// ==6664== For lists of detected and suppressed errors, rerun with: -s
// ==6664== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0
//
//
// Double free:
// ==6883== Memcheck, a memory error detector
// ==6883== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
// ==6883== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
// ==6883== Command: ./a.out
// ==6883==
// 45
// ==6883== Invalid free() / delete / delete[] / realloc()
// ==6883==    at 0x484412F: free (vg_replace_malloc.c:974)
// ==6883==    by 0x1091FE: main (val.c:20)
// ==6883==  Address 0x4ade040 is 0 bytes inside a block of size 40 free'd
// ==6883==    at 0x484412F: free (vg_replace_malloc.c:974)
// ==6883==    by 0x1091F2: main (val.c:19)
// ==6883==  Block was alloc'd at
// ==6883==    at 0x4841848: malloc (vg_replace_malloc.c:431)
// ==6883==    by 0x10916A: main (val.c:6)
// ==6883==
// ==6883==
// ==6883== HEAP SUMMARY:
// ==6883==     in use at exit: 0 bytes in 0 blocks
// ==6883==   total heap usage: 2 allocs, 3 frees, 1,064 bytes allocated
// ==6883==
// ==6883== All heap blocks were freed -- no leaks are possible
// ==6883==
// ==6883== For lists of detected and suppressed errors, rerun with: -s
// ==6883== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0
