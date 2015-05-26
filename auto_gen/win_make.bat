echo Press any key to continue...
pause

latex PearLogo
rem dvips -Ppdf PearLogo.dvi
rem ps2eps -B -C PearLogo.ps 
xelatex PearLogo.tex
rem pdftops -eps PearLogo.pdf PearLogo.eps
pdftops -eps PearLogo.pdf PearLogo.eps
ps2eps -f -B -C PearLogo.eps

del  *.toc  /s
del  *.out  /s
del  *.aux  /s
del  *.log  /s
del  *.bak  /s
rem del  *.dvi  /s
del  *.blg  /s
del  *.snm  /s
del  *.nav  /s
