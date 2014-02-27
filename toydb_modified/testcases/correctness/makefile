all: a.out

test: test_insert1 test_insert2 test_delete1 test_delete2 test_scan_gt test_scan2_gt test_scan_lt test_scan2_lt test_scan_ge test_scan2_ge test_scan_le test_scan2_le test_scan_eq test_scan2_eq test_scan_ne test_scan2_ne

a.out : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o main.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o main.o amscan.o amprint.o 

test_insert1: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_insert1.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_insert1.o amscan.o amprint.o -o test_insert1

test_insert1.o: test_insert1.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_insert1.c

test_insert2: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_insert2.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_insert2.o amscan.o amprint.o -o test_insert2	

test_insert2.o: test_insert2.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_insert2.c

test_delete1: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_delete1.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_delete1.o amscan.o amprint.o -o test_delete1

test_delete1.o: test_delete1.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_delete1.c

test_delete2: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_delete2.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_delete2.o amscan.o amprint.o -o test_delete2

test_delete2.o: test_delete2.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_delete2.c

test_scan_ne: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan_ne.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan_ne.o amscan.o amprint.o -o test_scan_ne

test_scan_ne.o: test_scan_ne.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan_ne.c

test_scan2_ne: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan2_ne.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan2_ne.o amscan.o amprint.o -o test_scan2_ne

test_scan2_ne.o: test_scan2_ne.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan2_ne.c

test_scan_eq: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan_eq.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan_eq.o amscan.o amprint.o -o test_scan_eq

test_scan_eq.o: test_scan_eq.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan_eq.c

test_scan2_eq: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan2_eq.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan2_eq.o amscan.o amprint.o -o test_scan2_eq

test_scan2_eq.o: test_scan2_eq.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan2_eq.c

test_scan_le: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan_le.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan_le.o amscan.o amprint.o -o test_scan_le

test_scan_le.o: test_scan_le.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan_le.c

test_scan2_le: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan2_le.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan2_le.o amscan.o amprint.o -o test_scan2_le

test_scan2_le.o: test_scan2_le.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan2_le.c

test_scan_ge: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan_ge.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan_ge.o amscan.o amprint.o -o test_scan_ge

test_scan_ge.o: test_scan_ge.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan_ge.c

test_scan2_ge: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan2_ge.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan2_ge.o amscan.o amprint.o -o test_scan2_ge

test_scan2_ge.o: test_scan2_ge.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan2_ge.c

test_scan_lt: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan_lt.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan_lt.o amscan.o amprint.o -o test_scan_lt

test_scan_lt.o: test_scan_lt.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan_lt.c

test_scan2_lt: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan2_lt.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan2_lt.o amscan.o amprint.o -o test_scan2_lt

test_scan2_lt.o: test_scan2_lt.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan2_lt.c

test_scan_gt: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan_gt.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan_gt.o amscan.o amprint.o -o test_scan_gt

test_scan_gt.o: test_scan_gt.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan_gt.c

test_scan2_gt: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan2_gt.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan2_gt.o amscan.o amprint.o -o test_scan2_gt

test_scan2_gt.o: test_scan2_gt.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan2_gt.c

amlayer.o : am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o amscan.o amprint.o
	ld -r am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o amscan.o amprint.o  -o amlayer.o

am.o : ../../amlayer/am.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c ../../amlayer/am.c

amfns.o : ../../amlayer/amfns.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c ../../amlayer/amfns.c

amsearch.o : ../../amlayer/amsearch.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c ../../amlayer/amsearch.c

aminsert.o : ../../amlayer/aminsert.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c ../../amlayer/aminsert.c

amscan.o : ../../amlayer/amscan.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c ../../amlayer/amscan.c

amstack.o : ../../amlayer/amstack.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c ../../amlayer/amstack.c

amglobals.o : ../../amlayer/amglobals.c ../../amlayer/am.h
	cc -w -g -c ../../amlayer/amglobals.c

amprint.o : ../../amlayer/amprint.c ../../amlayer/am.h ../../amlayer/pf.h 
	cc -w -g -c ../../amlayer/amprint.c
	
main.o : ../../amlayer/main.c ../../amlayer/am.h ../../amlayer/pf.h 
	cc -w -g -c ../../amlayer/main.c

#test1.o : test1.c ../../amlayer/am.h ../../amlayer/pf.h
#	cc -w -g -c test1.c

#test2.o : test2.c ../../amlayer/am.h ../../amlayer/pf.h
#	cc -w -g -c test2.c

#test3.o : test3.c ../../amlayer/am.h ../../amlayer/pf.h
#	cc -w -g -c test3.c

clean: 
	@rm -f *.o
	@rm -f *.out
	@rm -f *~
	@rm -f testrel.*
	@rm -f test_scan2_lt test_scan_gt test_scan2_gt test_scan_lt test_scan2_ge test_scan_ge test_scan2_le test_scan_le test_scan2_eq test_scan_eq test_scan2_ne test_scan_ne test_insert1 test_insert2 test_delete2 test_delete1
