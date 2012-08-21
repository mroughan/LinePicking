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

BIBTEX = /usr/bin/bibtex -min-crossrefs=50 
LATEX  = /usr/bin/latex -interaction=nonstopmode
PS2PDF = /usr/bin/ps2pdf
DVIPS = /usr/bin/dvips

SRCFILES := $(shell ls *.tex)
ROOT = $(SRCFILES:.tex=)
PS = $(SRCFILES:.tex=.ps)
PDF = $(SRCFILES:.tex=.pdf)
BIB = $(SRCFILES:.tex=.bib)
BBL = $(SRCFILES:.tex=.bbl)
DVI = $(SRCFILES:.tex=.dvi)


all: pdf
pdf: ${PDF} 
ps: ${PS}
dvi: ${DVI}
bbl: ${BBL}
bib: ${BIB}

# rules for slides
$(PS): %.ps: %.dvi
	${DVIPS} -f $^ > $@  

$(PDF): %.pdf: %.ps
	${PS2PDF} $^ $@ 

$(DVI): %.dvi: %.tex FORCE
	${LATEX} $< 
	${LATEX} $< 
	-${BIBTEX} $(<:.tex=)
	${LATEX} $< 

# other latex files
%.bbl: %.tex ${BIB}
	-${BIBTEX} $(<:.tex=)

%.bib: %.tex ${BIB}
	/home/mroughan/bin/bibextract.pl $< > $@

# cause latex to run every time I type make
FORCE:

# standard cleanup etc
.PHONY : clean
clean: 
	-rm *.dvi *.out *.log *.aux *.ps *~

.PHONY : distclean
distclean: 
	-rm *.dvi *.out *.log *.aux *.ps *~ *.pdf


