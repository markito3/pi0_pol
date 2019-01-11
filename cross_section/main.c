#include <stdio.h>
#include <gsl/gsl_integration.h>

#include "integrand.h"

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

  mpi = 135.0d;
  s = 4*mpi*mpi + .001d + 5000.0d;

  integrand.function = &func;
  params_in.s = s;
  params_in.mpi = mpi;
  params_in.r_or_i = 0;
  integrand.params = &params_in;

  n = 1024*128;
  limit = (int)n;
  workspace = gsl_integration_workspace_alloc(n);

  z = eval(integrand);
  printf("z = %f\n", z);

  a = 0.0d;
  b = 1.0d;
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
