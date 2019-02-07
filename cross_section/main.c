#include <stdio.h>
#include <gsl/gsl_integration.h>

#include "integrand.h"

int main() {

  gsl_function integrand;
  struct integrand_params params_in;
  double z;
  double s, s_out, mpi;
  double a, b, epsabs, epsrel;
  double result, abserr, result_z[2];
  size_t neval;
  int status;
  gsl_integration_workspace *workspace;
  size_t n;
  int limit, roi, npoints;
  FILE *out;

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

  out = fopen("integral.txt", "w");
  npoints = 0;
  for (s = 4*mpi*mpi + .001d; s < 1000000.0d; s += 10000.0d) {
    npoints++;
    params_in.s = s;
    for (roi = 0; roi < 2; roi++) { 
      params_in.r_or_i = roi;
  /*
      status = gsl_integration_qng(&integrand, a, b, epsabs, epsrel, &result, &abserr, &neval);
  */
      status = gsl_integration_qag(&integrand, a, b, epsabs, epsrel, limit, GSL_INTEG_GAUSS15, workspace, &result, &abserr);
      printf("npoints = %d, s = %f, roi = %d, result = %f, abserr = %f, neval = %d\n", npoints, s, roi, result, abserr, neval);
      result_z[roi] = result; 
    }
    s_out = sqrt(s*1.0E-6);
    fprintf(out, "%f %f %f\n", s_out, result_z[0], result_z[1]);
  }
  printf("npoints = %d\n", npoints);

  fclose(out);

  gsl_integration_workspace_free(workspace);

  return 0;

}
