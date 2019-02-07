      program integral
      implicit none
#include "integrand.inc"
      real*4 integrand, value, x
      real*4 a, b, epsabs, epsrel
      integer*4 key, limit
      parameter (limit = 1000)
      integer*4 neval, ier, iord, last
      real*4 result, abserr
      real*4 alist(limit), blist(limit), rlist(limit), elist(limit)
      external integrand
      rori = 0
      mpi = 135.0
      s = 4.0*mpi*mpi + .001 + 5000.0
      x = .5
      value = integrand(x)
      write (6, *) x, s, value
      a = 0.0
      b = 1.0
      epsabs = 0.001
      epsrel = 0.001
      key = 3
      call qage(integrand,a,b,epsabs,epsrel,key,limit,result,abserr,
     *   neval,ier,alist,blist,rlist,elist,iord,last)
      stop
      end

      
