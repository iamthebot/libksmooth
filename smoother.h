#pragma once
#include <stdlib.h>
#include <glib.h>
#include <ksmooth/kernels.h>
#include <ksmooth/scheduler.h>

// Nadaraya-Watson smoother
typedef struct ksmooth_nw_smoother_t {
    unsigned int concurrency;
    double (*dkernel)(double); // kernel to use for smoothing floats
    float (*fkernel)(float);   // kernel to use for smoothing doubles
    GMutex* mut;               // used to make smoother thread-safe
    ksmooth_bounds_t* bounds;  // used to store computed per-thread bounds
} ksmooth_nw_smoother_t;

typedef struct ksmooth_thread_payload_t {
    unsigned int tid; // thread id
    void* smoother;
    void* input_arr;
    void* output_arr;
    size_t start_idx;
    size_t end_idx;
} ksmooth_thread_payload_t;

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
