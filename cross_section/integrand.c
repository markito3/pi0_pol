#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_integration.h>

struct integrand_params {
  double a;
  double b;
};

double funcx(double x, void *parameters) {
  double c, y;
  struct integrand_params *these_params = (struct integrand_params *)parameters; 
  c = (these_params->a);
  y = c*x*x;
  printf("c = %f, x = %f, y = %f\n", c, x, y);
  return y;
}

double func(double x, void *parameters) {
  double s, mpi, arg, y;
  struct integrand_params *these_params = (struct integrand_params *)parameters; 
  s = (these_params->a);
  mpi = (these_params->b);
  arg = 1.0 - (s/(mpi*mpi))*x*(1.0 - x);
  y = log(arg)/x;
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
  s = 4*mpi*mpi - 10.0;

  integrand.function = &func;
  params_in.a = s;
  params_in.b = mpi;
  integrand.params = &params_in;

  n = 1024;
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
