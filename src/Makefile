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

MEX = LinePicking.mexa64
O = LinePicking.o beta.o
SO = LinePicking.so beta.so
STAND_ALONE = LinePicking 

all: ${STAND_ALONE}

test: LinePicking
	LinePicking -f test.dat -m 1 

$(O): %.o: %.c ${HEADERS}
	$(CC) $< -c -o $@ -I/usr/include/ -D_STANDALONE

$(STAND_ALONE): %: %.o beta.o
	$(CC) $< -o $@ beta.o -lm -lstdc++ -D_STANDALONE

# use to create MEX library for MATLAB
$(MEX): %.mexa64: %.c beta.o ${HEADERS}
	$(MX)  $< beta.o -D_MEX

# shared libraries are used by R, so use R's standard command to define
#    see R CMD SHLIB beta.c, for example
$(SO): %.so: %.c ${HEADERS}
	$(CC) -std=gnu99 -shared $< -o $@ -D_R -I/usr/include/ -I/usr/share/R/include/ -L/usr/lib64/R/lib -lR

# $(O): %.o: %.c ${HEADERS}
# 	$(CC) $< -c -o $@ -I/usr/include/ -I/usr/local/matlab/extern/include/ 

# $(STAND_ALONE): %: %.o
# 	$(CC) $< -o $@ -L/usr/local/matlab/bin/glnxa64 -lmx -lmex -lmat -lm -lstdc++

# cause something to always remake when you put this in its dependencies
FORCE:

# standard cleanup etc
.PHONY : clean
clean: 
	- $(RM) *.dll *.oct *.o *.so *~

.PHONY : distclean
distclean: 
	- $(RM) LinePicking *.mex* *.dll *.oct *.o *.so *~

