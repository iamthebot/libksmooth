# libksmooth
NOTE: this library is still in active development. Please do not use it yet.

##Introduction
libksmooth implements a collection of functions to perform fast, memory-efficient smoothing of large datasets. Supported kernel smoothing variants include Nadaraya-Watson. Smoothing is performed concurrently and library functions are thread-safe (provided the same smoother is shared among multiple calling threads).

Cross-platform compatibility (linxu and windows) is provided using glib2.

##Dependencies
 - glib2

##Usage
First, create a new smoother of the desired type and kernel:
```c
...
#include <ksmooth/smoother.h>
ksmooth_nw_smoother_t * mysmoother;
mysmoother = ksmooth_new_nw_smoother(KSMOOTH_KERNEL_GAUSSIAN);
```

Second, set concurrency (number of concurrent threads used for computation). for the smoother. If you don't set this, it will simply default to the number of cores on the machine.
```c
...
ksmooth_set_concurrency(mysmoother, 8);
```

Third, create a place to store the results. You are responsible for making sure the size of this array is >= the size of the input array.
```c
...
double *myoutput = calloc(100000,sizeof(double));
//or
float *myoutput = calloc(10000,sizeof(double));
```

Fourth, call the smoothing function for the desired type with the desired bandwidth.
```c
//input data = myinput
//output data = myoutput
//data length = 100000
//bandwidth = 1000

//if float
int status = ksmooth_nw_fsmooth(mysmoother, myinput, myoutput, 100000, 1000);
if(!status)
    printf("something happened...\n");

//if double
int status = ksmooth_nw_dsmooth(mysmoother, myinput, myoutput, 100000, 1000);
if(!status)
    printf("something happened...\n");
```

Finally, destroy your smoother object when you're done:
```c
ksmooth_destroy(mysmoother);
```
