#pragma once
#include <ksmooth/smoother.h>

typedef enum { KSMOOTH_KERNEL_GAUSSIAN } ksmooth_kernel;

typedef enum { KSMOOTH_OK, KSMOOTH_INVALID_BOUNDS } ksmooth_status;

// create new Nadaraya-Watson smoother
ksmooth_nw_smoother_t ksmooth_new_nw_smoother(ksmooth_kernel k);

// set concurrency level for smoother. If not called, default is number of cores on machine.
void ksmooth_set_concurrency(void* smoother);

// free resources associated with Nadaraya-Watson smoother
void ksmooth_destroy_nw_smoother(ksmooth_nw_smoother_t* s);

// smooth array of floats with given size and bandwidth. Returns 0 if OK.
int ksmooth_nw_fsmooth(ksmooth_nw_smoother_t* s, float* input, float* output, size_t size, long long bandwidth);

// smooth array of doubles with given size and bandwidth. Returns 0 if OK.
int ksmooth_nw_dsmooth(ksmooth_nw_smoother_t* s, double* input, float* output, size_t size, long long bandwidth);
