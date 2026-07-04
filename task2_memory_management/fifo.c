#include <stdio.h>
int main()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frameCount;
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);
    int frames[frameCount];
    int hits = 0;
    int faults = 0;
    int pointer = 0;
    // Initialize frames
    for (int i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
    }
    printf("\nFIFO Page Replacement Simulation\n");
    printf("Page Frames Result\n");
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        // Check if page is already in memory
        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                hits++;
                break;
            }
        }
        // Page fault
        if (!found)
        {
            frames[pointer] = pages[i];
            pointer = (pointer + 1) % frameCount;
            faults++;
        }

        // Display current frames
        printf("%d\t", pages[i]);
        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        if (found)
            printf("\tHit");
        else
            printf("\tFault");
        printf("\n");
    }
    printf("Total References : %d\n", n);
    printf("Page Hits : %d\n", hits);
    printf("Page Faults: %d\n", faults);
    printf("Hit Ratio : %.2f%%\n", (hits * 100.0) / n);
    printf("Miss Ratio: %.2f%%\n", (faults * 100.0) / n);
    return 0;
}
