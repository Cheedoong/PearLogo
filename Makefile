all:	clean pdf eps clean

pdf:
	xelatex PearLogo.tex

eps:
	pdftops -eps PearLogo.pdf PearLogo.eps
	ps2eps -f -B -C PearLogo.eps

clean:
	rm -f *.aux *.log *.blg *.bbl *.out *.dvi *.ps *.fff *.lof
