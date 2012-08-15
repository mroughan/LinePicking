#=============================================================================
# Makefile: for line picking problem
# Matthew Roughan (c) 2012
#     this program is distributed under the terms of the 
#     GNU General Public License
#
#=============================================================================

default: all

#-----------------------------------------------------------------------------

MX=mex -O -largeArrayDims 
CC=gcc -O -fPIC

C = $(shell ls *.c)
HEADERS = $(shell ls *.h)
MEX := $(shell ls *.mexa64)
O = $(MEX:.mexa64=.o)
STAND_ALONE = $(MEX:.mexa64=)


all: ${MEX} ${STAND_ALONE}

test: distance_dist
	distance_dist -f distance_dist_test.inp -m 1 

$(MEX): %.mexa64: %.c ${HEADERS}
	$(MX)  $< -D_MEX

$(O): %.o: %.c ${HEADERS}
	$(CC) $< -c -o $@ -I/usr/include/

$(STAND_ALONE): %: %.o
	$(CC) $< -o $@ -lm -lstdc++

# $(O): %.o: %.c ${HEADERS}
# 	$(CC) $< -c -o $@ -I/usr/include/ -I/usr/local/matlab/extern/include/ 

# $(STAND_ALONE): %: %.o
# 	$(CC) $< -o $@ -L/usr/local/matlab/bin/glnxa64 -lmx -lmex -lmat -lm -lstdc++

# cause something to always remake when you put this in its dependencies
FORCE:

# standard cleanup etc
.PHONY : clean
clean: 
	- $(RM) *.mex* *.dll *.oct *.o

.PHONY : distclean
distclean: 
	- $(RM) *.mex* *.dll *.oct *.o

