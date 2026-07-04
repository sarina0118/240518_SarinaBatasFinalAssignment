#include <stdio.h>
int main()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frameCount;
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);
    int frames[frameCount];
    int lastUsed[frameCount];
    int hits = 0;
    int faults = 0;
    // Initialize frames
    for (int i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
        lastUsed[i] = -1;
    }
    printf("\nLRU Page Replacement Simulation\n");
    printf("Page Frames Result\n");
    for (int time = 0; time < n; time++)
    {
        int page = pages[time];
        int found = 0;
        // Check if page is already in memory
        for (int i = 0; i < frameCount; i++)
        {
            if (frames[i] == page)
            {
                found = 1;
                hits++;
                lastUsed[i] = time;
                break;
            }
        }
        // Page fault
        if (!found)
        {
            faults++;
            int empty = -1;
            // Find an empty frame
            for (int i = 0; i < frameCount; i++)
            {
                if (frames[i] == -1)
                {
                    empty = i;
                    break;
                }
            }

            if (empty != -1)
            {
                frames[empty] = page;
                lastUsed[empty] = time;
            }
            else
            {
                // Find least recently used page
                int lru = 0;
                for (int i = 1; i < frameCount; i++)
                {
                    if (lastUsed[i] < lastUsed[lru])
                        lru = i;
                }
                frames[lru] = page;
                lastUsed[lru] = time;
            }
        }
        printf("%d\t", page);
        for (int i = 0; i < frameCount; i++)
        {
            if (frames[i] == -1)
                printf("- ");
            else
                printf("%d ", frames[i]);
        }
        if (found)
            printf("\tHit");
        else
            printf("\tFault");
        printf("\n");
    }
    printf("Total References : %d\n", n);
    printf("Page Hits: %d\n", hits);
    printf("Page Faults: %d\n", faults);
    printf("Hit Ratio: %.2f%%\n", (hits * 100.0) / n);
    printf("Miss Ratio: %.2f%%\n", (faults * 100.0) / n);
    return 0;
}
