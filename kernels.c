#include <ksmooth/kernels.h>
#include <math.h>

double ksmooth_dgaussian(double x, double s)
{
    return OSQRT2PI * (1.0 / s) * exp(-0.5 * (x * x) / (s * s));
}

float ksmooth_fgaussian(float x, float s)
{
    return OSQRT2PI * (1.0 / s) * expf(-0.5 * (x * x) / (s * s));
}
