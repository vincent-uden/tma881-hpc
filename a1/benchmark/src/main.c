// Results of compiling with different levels of optimization
// O0: 1.335851 seconds
// O1: 0.227119 seconds
// O2: 0.0 seconds
// O3: 0.0 seconds
// Og: 0.346106 seconds
//
// Example compilation command: gcc ./src/main.c -O1 -o O1.out
//
// O2 and O3 probably manages use the gauss summation formula or something
// similiar to deconstruct the loop into a single statement. The resulting
// binaries are of similar size but after comparing the binary output of O0 and
// O3 practically all of the 16kb are just padding.
//
// Taking a closer look at the generated assembly from running:
// gcc -c -S -O0 src/main.c
// gcc -c -S -O3 src/main.c
// We can compare these relevant lines for a good clue
// --- O0.s ---
// .L3:
// 	movl	-68(%rbp), %eax
// 	cltq
// 	addq	%rax, -64(%rbp)
// 	addl	$1, -68(%rbp)
// .L2:
// 	cmpl	$999999999, -68(%rbp)
// 	jle	.L3
//
// --- O3.s ---
// movabsq	$499999999500000000, %rsi
//
// The unoptimized code actually uses our condition, looping up to a billion
// and repeatedly increments the %rbp register holding our i variable.
//
// The opimized code not only figured out how to short-circuit our summation
// but actually hard-coded the resulting integer itself into the assembly

#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval startTime;
    gettimeofday(&startTime, NULL);

    long sum = 0;
    for (int i = 0; i < 1000000000; ++i) {
        sum += i;
    }

    struct timeval end;
    gettimeofday(&end, NULL);

    long duration = 0;
    duration += (end.tv_sec - startTime.tv_sec) * 1000000;
    duration += (end.tv_usec - startTime.tv_usec);

    printf("The sum of the first billion integers is %ld \n", sum);
    printf("This summation took %ld.%ld seconds \n", duration / 1000000, duration % 1000000);
}

