#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_integration.h>
#define PI 3.14159265359

struct integrand_params {
  double s;
  double mpi;
  int r_or_i;
};

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

int main() {

  gsl_function integrand;
  struct integrand_params params_in;
  double z;
  double s, mpi;
  double a, b, epsabs, epsrel;
  double result, abserr;
  size_t neval;
  int status;
  gsl_integration_workspace *workspace;
  size_t n;
  int limit;

  mpi = 135.0;
  s = 4*mpi*mpi + .001 + 5000.;

  integrand.function = &func;
  params_in.s = s;
  params_in.mpi = mpi;
  params_in.r_or_i = 1;
  integrand.params = &params_in;

  n = 1024*128;
  limit = (int)n;
  workspace = gsl_integration_workspace_alloc(n);

  z = eval(integrand);
  printf("z = %f\n", z);

  a = 0.0;
  b = 1.0;
  epsabs = 1.e-3;
  epsrel = 1.e-3;
  
  /*
  status = gsl_integration_qng(&integrand, a, b, epsabs, epsrel, &result, &abserr, &neval);
  */
  status = gsl_integration_qag(&integrand, a, b, epsabs, epsrel, limit, GSL_INTEG_GAUSS15, workspace, &result, &abserr);
  printf("result = %f, abserr = %f, neval = %d\n", result, abserr, neval);

  gsl_integration_workspace_free(workspace);

  return 0;

}
