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

# recursive structure from
#   http://lackof.org/taggart/hacking/make-example/
# which also appears in gnu makes docs: http://www.gnu.org/software/make/manual/make.html#Phony-Targets
# 

SUBDIRS = src Matlab  R man 

.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)

$(SUBDIRS): FORCE
	$(MAKE) -C $@ -f gMakefile

# cause something to always remake when you put this in its dependencies
FORCE:

# standard cleanup
.PHONY: clean
clean: 
	echo cleaning up in .
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) -f gMakefile clean ); done


# don't build Matlab, or R until after src is built
Matlab: src
R: src
