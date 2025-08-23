LATEX = /usr/local/texlive/2023/bin/x86_64-linux/pdflatex
LATEXFLAGS = -interaction=nonstopmode

all: refman.pdf

refman.pdf: refman.tex
	$(LATEX) $(LATEXFLAGS) refman.tex
	$(LATEX) $(LATEXFLAGS) refman.tex
	rm -f *.aux *.log *.toc *.idx *.ilg *.ind

clean:
	rm -rf *.pdf
	rm -rf *.aux *.log *.toc *.dvi