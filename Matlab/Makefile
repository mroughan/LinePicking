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

MEX = distance_dist.mexa64

.PHONY: mex $(MEX)
mex: $(MEX)

$(MEX): FORCE
	cd ../src/; $(MAKE) $@; cp $@ ../Matlab/

# cause something to always remake when you put this in its dependencies
FORCE:

# standard cleanup etc
.PHONY : clean
clean: 
	- $(RM) *~

.PHONY : distclean
distclean: 
	- $(RM) *.mex* Plots/distance_dist*

