all: a.out

a.out : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o main.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../pflayer/pflayer.o main.o amscan.o amprint.o 

t1 : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o test1.o amscan.o amprint.o
	cc -w -g -o t1.out am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../pflayer/pflayer.o test1.o amscan.o amprint.o

t2 : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o test2.o amscan.o amprint.o
	cc -w -g -o t2.out am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../pflayer/pflayer.o test2.o amscan.o amprint.o

#t3 : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../pflayer/pflayer.o test3.o amscan.o amprint.o
#	cc -w -g -o t1.out am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../pflayer/pflayer.o test1.o amscan.o amprint.o

amlayer.o : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o amscan.o amprint.o
	ld -r am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o amscan.o amprint.o  -o amlayer.o

am.o : am.c am.h pf.h
	cc -w -g -c am.c

amfns.o : amfns.c am.h pf.h
	cc -w -g -c amfns.c

amsearch.o : amsearch.c am.h pf.h
	cc -w -g -c amsearch.c

aminsert.o : aminsert.c am.h pf.h
	cc -w -g -c aminsert.c

amscan.o : amscan.c am.h pf.h
	cc -w -g -c amscan.c

amstack.o : amstack.c am.h pf.h
	cc -w -g -c amstack.c

amglobals.o : amglobals.c am.h
	cc -w -g -c amglobals.c

amprint.o : amprint.c am.h pf.h 
	cc -w -g -c amprint.c
	
main.o : main.c am.h pf.h 
	cc -w -g -c main.c

test1.o : test1.c am.h pf.h
	cc -w -g -c test1.c

test2.o : test2.c am.h pf.h
	cc -w -g -c test2.c

test3.o : test3.c am.h pf.h
	cc -w -g -c test3.c

clean: 
	@rm -f *.o
	@rm -f *.out
	@rm -f *~
	@rm -f testrel.*
