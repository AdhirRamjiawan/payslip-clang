SHELL := /bin/bash
FLAWFINDER := /opt/homebrew/bin/flawfinder

all:
	gcc main.c html.h html.c 
	mv a.out payslip
	$(FLAWFINDER) . 

clean:
	rm -f ./payslip
	rm -Rf ./*.dSYM
	rm -f *.gch
	rm -f *.pch

debug:
	gcc -g main.c html.h html.c 
	mv a.out payslip
	mv a.out.dSYM payslip.dSYM

code:
	vim -p main.c html.c html.h

setup:
	brew install flawfinder
