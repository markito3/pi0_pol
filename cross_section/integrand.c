#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_integration.h>

#include "integrand.h"

#define PI 3.14159265359

double funcx(double x, void *parameters) {
  double c, y;
  struct integrand_params *these_params = (struct integrand_params *)parameters; 
  c = (these_params->s);
  y = c*x*x;
  printf("c = %f, x = %f, y = %f\n", c, x, y);
  return y;
}

double func(double x, void *parameters) {
  double s, mpi, arg, y;
  int r_or_i;
  struct integrand_params *these_params = (struct integrand_params *)parameters; 
  s = (these_params->s);
  mpi = (these_params->mpi);
  r_or_i = these_params->r_or_i;
  arg = 1.0d - (s/(mpi*mpi))*x*(1.0d - x);
  if (r_or_i == 0) { /* real part */
    y = log(fabs(arg))/x;
  } else { /* imaginary part */
    if (arg >= 0.0d) {
      y = 0.0d;
    } else {
      y = -PI/x;
    }
  }

  printf("s = %f, mpi = %f, x = %f, arg = %f, y = %f\n", s, mpi, x, arg, y);
  return y;
}

double eval(gsl_function func_in) {
  double x, y;
  void *params;
  x=7.0;
  params = func_in.params;
  y = func_in.function(x, params);
  return y;
}
