#=============================================================================
# Makefile: for line picking problem
#
# Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
#     This program is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
# 
#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with this program.  If not, see <http://www.gnu.org/licenses/>.
# 
#
#=============================================================================

default: all

#-----------------------------------------------------------------------------

MX=mex -O -largeArrayDims 
CC=gcc -O -fPIC

C = $(shell ls *.c)
HEADERS = $(shell ls *.h)

MEX = distance_dist.mexa64
O = distance_dist.o beta.o
STAND_ALONE = distance_dist 

all: ${STAND_ALONE}

test: distance_dist
	distance_dist -f distance_dist_test.inp -m 1 

$(MEX): %.mexa64: %.c beta.o ${HEADERS}
	$(MX)  $< beta.o -D_MEX

$(O): %.o: %.c ${HEADERS}
	$(CC) $< -c -o $@ -I/usr/include/ -D_STANDALONE

$(STAND_ALONE): %: %.o beta.o
	$(CC) $< -o $@ beta.o -lm -lstdc++ -D_STANDALONE

# $(O): %.o: %.c ${HEADERS}
# 	$(CC) $< -c -o $@ -I/usr/include/ -I/usr/local/matlab/extern/include/ 

# $(STAND_ALONE): %: %.o
# 	$(CC) $< -o $@ -L/usr/local/matlab/bin/glnxa64 -lmx -lmex -lmat -lm -lstdc++

# cause something to always remake when you put this in its dependencies
FORCE:

# standard cleanup etc
.PHONY : clean
clean: 
	- $(RM) *.dll *.oct *.o *~

.PHONY : distclean
distclean: 
	- $(RM) distance_dist *.mex* *.dll *.oct *.o *~

