CC 	= gcc
CFLAGS 	= -Wall -std=c99
INCLUDES  = 
LIBS 	= -pthread
SRCS 	= buffer.c test1.c
TEX	= latex -shell-escape
BIBTEX	= bibtex
DVIPS	= dvips
DVIPDF  = dvipdft
XDVI	= xdvi -gamma 4
GH	= gv
RC	:= $(shell egrep -l '^[^%]*\\begin\{document\}' *.tex)
TRG	= $(SRC:%.tex=%.dvi)
PSF	= $(SRC:%.tex=%.ps)
PDF	= $(SRC:%.tex=%.pdf)

#pdf: $(PDF)

#ps: $(PSF)

#$(TRG): %.dvi: %.tex $(TRG)
	#one way of including source code is to use pygments
#	pygmentize -f latex -o __${TRG}.tex ${TRG}
	#requires that you \include{pygments.tex} in your preamble

#	$(LATEX) $<
#	$(BIBTEX) $(<:%.tex=%)
#	$(LATEX) $<
#	$(LATEX) $<
	#remove the pygmentized output to avoid cluttering up the directory
	#rm __${SRC}.tex


#$(PSF):%.ps: %.dvi
#	$(DVIPS) -R -Poutline -t letter $< -o $@

#$(PDF): %.pdf: %.ps
#	ps2pdf $<i


concurrency.o: concurrency.c buffer.c
	$(CC) $(CFLAGS) -c $(LIBS) concurrency.c 

buffer.o: buffer.c buffer.h
	$(CC) $(CFLAGS) -c $(LIBS) buffer.c

mt.o: mt19937ar.c mt19937ar.h
	$(CC) $(CFLAGS) -c mt19937ar.c
latex: *.tex
	pdflatex writeup.tex

clean:
	rm -f *.o *.out *.dvi *.out *.log *.aux *.bbl *.blg *.pyg *.toc *.pdf

all: latex
	$(CC) $(CFLAGS) $(LIBS)

