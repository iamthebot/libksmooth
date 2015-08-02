#pragma once
#include <stdlib.h>
#include <glib.h>
#include <czmq.h>
#include <ksmooth/kernels.h>
#include <ksmooth/scheduler.h>

// Nadaraya-Watson smoother
typedef struct ksmooth_nw_smoother_t {
    unsigned int c;            // concurrency level (i.e. # of threads)
    double (*dkernel)(double); // kernel to use for smoothing floats
    float (*fkernel)(float);   // kernel to use for smoothing doubles
    GMutex* mut;               // used to make smoother thread-safe
    ksmooth_task_t* tasks;     // used to store tasks dispatched to threads
    zsock_t* th_q_arr;         // used to dispatch tasks to threads
} ksmooth_nw_smoother_t;

// task for thread to work on
typedef struct ksmooth_task_t {
    void* input_arr;  // our input
    void* output_arr; // our output
    size_t size;      // array size to look at
    size_t start;     // starting index for smoothing
    size_t end;       // ending index for smoothing
    bool shutdown;    // whether we should ignore the other stuff and shutdown the thread
} ksmooth_bounds_t;

// What we pass to each thread at creation
typedef struct ksmooth_th_init_data_t {
    unsigned int tid;  // thread id
    zsock_t* thread_q; // queue to receive tasks from
} ksmooth_init_data_t;

// gets bounds of array for each thread to work on
void ksmooth_nw_get_tasks(ksmooth_nw_smoother_t* smoother, unsigned int c, size_t len);
