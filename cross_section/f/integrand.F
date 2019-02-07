      real*4 function integrand(x)
      implicit none
#include "integrand.inc"
      real x, y, arg
      arg = 1 - (s/mpi**2)*x*(1 - x)
      if (arg .lt. 0.0) then
         if (rori .eq. 0) then
            arg = abs(arg)
            y = log(arg)/x
         else
            y = -PI/x
         end if
      else
         if (rori .eq. 0) then
            y = log(arg)/x
         else
            y = 0.0
         end if
      end if
      integrand = y
      end
