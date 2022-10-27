/**
 * Benchmark to measure Linux' methods to do syscall.
 * Measure's getpid() using Intel CPU's rdtsc, using
 *    - libc' getpid()
 *    - using syscall instruction
 *    - using the venerable "int 0x80"
 *
 * Copyright 2013-2018, Rainer Keller, HS Esslingen
 * This will seg-fault after(!) printf() with gcc-4.4.7.
 */
#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

#define NUM_TIMES 1000

// #define DEBUG(x)    x
#define DEBUG(x)

unsigned long long int getrdtsc (void)
{
	unsigned int hi, lo;
	__asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));

	return ( ((unsigned long long int)hi << 32) |
                 (unsigned long long int)lo);
}


long int my_getpid(void)
{
    long int pid;
    __asm__ __volatile__(
        "movl $0x27, %%eax\n\t"
        "int $0x80\n\t"
        : "=a" ((long int)pid) /* output */
        : /* input */
        : "memory");   /* clobbers */
    return pid;
}

int main(int argc, char * argv[]) {
    long int ID1, ID2, ID3;
    unsigned long long int tsc_start, tsc_stop;
    double tsc_syscall = 0.0, tsc_libc = 0.0, tsc_int80 = 0.0;
    int i;

    DEBUG(printf("Timing: Measure libc getpid()"));
    tsc_start = getrdtsc ();
    for (i = 0; i < NUM_TIMES; i++)
    	ID1 = getpid();
    tsc_stop = getrdtsc ();
    tsc_libc = (tsc_stop - tsc_start) / (double)NUM_TIMES;
    DEBUG(printf (":%.2f\n", tsc_libc));

    DEBUG(printf("Timing: Measure direct syscall SYS_getpid"));
    tsc_start = getrdtsc ();
    for (i = 0; i < NUM_TIMES; i++)
	ID2 = syscall(SYS_getpid);
    tsc_stop = getrdtsc ();
    tsc_syscall = (tsc_stop - tsc_start) / (double)NUM_TIMES;
    DEBUG(printf (":%.2f\n", tsc_syscall));

    DEBUG(printf("Timing: Measure Assembler sequence"));
    tsc_start = getrdtsc ();
    for (i = 0; i < NUM_TIMES; i++)
    	ID3 = my_getpid();
    tsc_stop = getrdtsc ();
    tsc_int80 = (tsc_stop - tsc_start) / (double)NUM_TIMES;
    DEBUG(printf (":%.2f\n", tsc_int80));

    printf("Timing: libc:%.2f direct syscall:%.2f ASM int 0x80:%.2f\n",
           tsc_libc, tsc_syscall, tsc_int80);

    return 0;
}
