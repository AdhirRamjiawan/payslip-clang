

clean:
	rm -f ./payslip
	rm -Rf ./*.dSYM
	rm -f *.gch

debug:
	gcc -g main.c html.h html.c memory.h
	mv a.out payslip
	mv a.out.dSYM payslip.dSYM

all:
	gcc main.c html.h memory.h html.c 
	mv a.out payslip
