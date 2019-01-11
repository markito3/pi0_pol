#ifndef _integrand_h_
#define _integrand_h__

struct integrand_params {
  double s;
  double mpi;
  int r_or_i;
};

double func(double x, void *parameters);
double eval(gsl_function func_in);

#endif
