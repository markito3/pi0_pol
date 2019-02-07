SOURCES = main.F integrand.F
INCLUDES = integrand.inc
BASENAMES = $(basename $(SOURCES))
OBJECTS = $(addsuffix .o, $(BASENAMES))

all: cross_section

.quadpack_make_done: 
	cd quadpack ; make
	date > $@

cross_section: $(OBJECTS) .quadpack_make_done
	gfortran -o $@ $(OBJECTS) -L quadpack -lquadpack

$(OBJECTS): $(INCLUDES)

%.o: %.F
	gfortran -c $<
