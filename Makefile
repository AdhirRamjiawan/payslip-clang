

all:
	gcc main.c html.h html.c 
	mv a.out payslip

clean:
	rm -f ./payslip
	rm -Rf ./*.dSYM
	rm -f *.gch

debug:
	gcc -g main.c html.h html.c 
	mv a.out payslip
	mv a.out.dSYM payslip.dSYM

code:
	vim -p main.c html.c html.h

setup:
	brew install flawfinder
