#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Basic timing routine
#include <timing.h>

// Advanced timer module
#include <types.h>
#include <timer.h>

int main (int argc, char** argv)
{
    CyclesData timeData;
    double S, E;
    printf("Timer Demo 1: Basic timing\n");

    //Basic example
    S = mysecond();
    sleep(3);
    E = mysecond();

    printf("Time: %e sec\n", E-S);

    //Advanced timer example
    printf("Timer Demo 2: Advance timer\n");
    timer_init();

    timer_startCycles(&timeData);
    sleep(3);
    timer_stopCycles(&timeData);

    printf("Cycles: %llu\n",LLU_CAST  timer_printCycles(&timeData));
    printf("Time: %e sec\n", timer_printCyclesTime(&timeData));

    return EXIT_SUCCESS;
}
