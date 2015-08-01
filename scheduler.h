#pragma once
#include <stdlib.h>
/*
 * Determines how to allocate smoothing tasks to threads
 */

typedef struct ksmooth_bounds_t {
    size_t start;
    size_t end;
} ksmooth_bounds_t;
