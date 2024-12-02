/**
 * Implement spin lock for a single core uC
 */

#include "../utils.h"

#define INTLOCK()
#define INTFREE()

void spin_lock_lock(bool *lock)
{
    while(*lock);
    INTLOCK();
    *lock = 1;
    INTFREE();
}

void spin_lock_unlock(bool *lock)
{
    INTLOCK();
    if(*lock)
    {
        *lock = 0;
    }
    INTFREE();
}