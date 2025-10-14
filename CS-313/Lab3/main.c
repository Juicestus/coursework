#include <stdint.h>
#include <stdio.h>
#include <threading.h>

void dosomething(int32_t x, int32_t y)
{
        for(int32_t i = x; i < y; i++)
        {
                // Perform some computation
                printf("Hi! (%d -> %d): Running: %d\n", x, y, i);
                t_yield();      // Yield the control to other workers
        }
        printf("Hi! (%d -> %d): Done!\n", x, y); // Perform some computation
        t_finish(); // All the work is done!
}

int main()
{
        t_init(); // Initialize the runtime

        if(t_create(dosomething, 0, 10) != 0) // Spawn a worker context
        {
                fprintf(stderr, "Could not spawn worker!\n");
                return -1;
        }

        if(t_create(dosomething, 10, 20) != 0) // Spawn a worker context
        {
                fprintf(stderr, "Could not spawn worker!\n");
                return -1;
        }

        if(t_create(dosomething, 20, 30) != 0) // Spawn a worker context
        {
                fprintf(stderr, "Could not spawn worker!\n");
                return -1;
        }

        while(t_yield() >= 1)
                ; // Wait for the workers to finish their tasks
        return 0;
}
