#include <stdio.h>
int main()
{
    int burst[] = {5, 3, 7};
    int remaining[] = {5, 3, 7};
    int n = 3;
    int quantum = 2;
    int time = 0;
    int completed = 0;
    printf("Round Robin Scheduling Simulation\n");
    printf("Time Quantum = %d\n\n", quantum);
    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (remaining[i] > 0)
            {
                printf("Time %2d -> Process P%d executes ", time, i + 1);
                if (remaining[i] > quantum)
                {
                    remaining[i] -= quantum;
                    time += quantum;
                    printf("for %d units\n", quantum);
                }
                else
                {
                    time += remaining[i];
                    printf("for %d units (Completed)\n", remaining[i]);
                    remaining[i] = 0;
                    completed++;
                }
            }
        }
    }
    printf("\nAll processes completed.\n");
    return 0;
}
