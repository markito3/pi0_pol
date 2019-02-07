SOURCES = qage.f  qk15.f  qk21.f  qk31.f  qk41.f  qk51.f  qk61.f  qpsrt.f r1mach.f d1mach.f i1mach.f
BASENAMES = $(basename $(SOURCES))
OBJECTS = $(addsuffix .o, $(BASENAMES))

libquadpack.a: $(OBJECTS)
	ar r $@ $(OBJECTS)

env:
	@echo $(SOURCES)
	@echo $(BASENAMES)
	@echo $(OBJECTS)

%.o: %.f
	gfortran -c $<
