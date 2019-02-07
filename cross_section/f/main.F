      program integral
      implicit none
#include "integrand.inc"
      real*4 integrand, value, x
      real*4 a, b, epsabs, epsrel
      integer*4 i
      integer*4 key, limit
      parameter (limit = 10000)
      integer*4 neval, ier, iord, last
      real*4 result, abserr
      real*4 alist(limit), blist(limit), rlist(limit), elist(limit)
      real*4 threshold
      real*4 result_z(2), s_out, g_real, g_imag, c1, c2
      external integrand
      rori = 0
      mpi = 135.0
      s = 4.0*mpi*mpi + .001 + 5000.0
      x = .5
      value = integrand(x)
      write (6, *) x, s, value
      a = 0.0
      b = 1.0
      epsabs = 0.0001
      epsrel = 0.0001
      key = 3
      call qage(integrand,a,b,epsabs,epsrel,key,limit,result,abserr,
     *   neval,ier,alist,blist,rlist,elist,iord,last)
      write (6,*) s, result
      threshold = 4.0*mpi*mpi + 100.
      c1 = -1.0/(4*PI)**2
      do s = threshold, 1000000.0, 10000.
         c2 = 2.0*mpi*mpi/s
         do i = 1, 2
            rori = i - 1;
            call qage(integrand,a,b,epsabs,epsrel,key,limit,result,
     *           abserr, neval,ier,alist,blist,rlist,elist,iord,last)
            write (6,*) rori, s, result, abserr, neval, ier
            result_z(i) = result
         end do
         s_out = s*1.e-6
         g_real = c1*(1.0+c2*result_z(1))
         g_imag = c1*(c2*result_z(2))
         write (20, *) s_out, g_real, g_imag
      end do
      stop
      end

      
