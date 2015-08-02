#pragma once

#ifndef PI
#define PI 3.14159265358979
#define OSQRT2PI 0.3989422804014
#endif

// computes gaussian PDF at point x with sdev s (double precision)
double ksmooth_dgaussian(double x, double s);

// computes gaussian PDF at point x with sdev s (single precision)
double ksmooth_fgaussian(float x, float s);
