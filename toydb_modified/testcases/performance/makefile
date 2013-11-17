all: test

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
	


am_old.o : ../../../toydb/amlayer/am.c ../../../toydb/amlayer/am.h ../../../toydb/amlayer/pf.h
	cc -w -g -c ../../../toydb/amlayer/am.c -o am_old.o

amfns_old.o : ../../../toydb/amlayer/amfns.c ../../../toydb/amlayer/am.h ../../../toydb/amlayer/pf.h
	cc -w -g -c ../../../toydb/amlayer/amfns.c -o amfns_old.o

amsearch_old.o : ../../../toydb/amlayer/amsearch.c ../../../toydb/amlayer/am.h ../../../toydb/amlayer/pf.h
	cc -w -g -c ../../../toydb/amlayer/amsearch.c -o amsearch_old.o

aminsert_old.o : ../../../toydb/amlayer/aminsert.c ../../../toydb/amlayer/am.h ../../../toydb/amlayer/pf.h
	cc -w -g -c ../../../toydb/amlayer/aminsert.c -o aminsert_old.o

amscan_old.o : ../../../toydb/amlayer/amscan.c ../../../toydb/amlayer/am.h ../../../toydb/amlayer/pf.h
	cc -w -g -c ../../../toydb/amlayer/amscan.c -o amscan_old.o

amstack_old.o : ../../../toydb/amlayer/amstack.c ../../../toydb/amlayer/am.h ../../../toydb/amlayer/pf.h
	cc -w -g -c ../../../toydb/amlayer/amstack.c -o amstack_old.o

amglobals_old.o : ../../../toydb/amlayer/amglobals.c ../../../toydb/amlayer/am.h
	cc -w -g -c ../../../toydb/amlayer/amglobals.c -o amglobals_old.o

amprint_old.o : ../../../toydb/amlayer/amprint.c ../../../toydb/amlayer/am.h ../../../toydb/amlayer/pf.h 
	cc -w -g -c ../../../toydb/amlayer/amprint.c -o amprint_old.o

test: test_new test_old

test_new: test_time_insert_new test_time_delete_new test_time_insert2_new test_time_delete2_new test_scan1_new test_scan2_new test_scan3_new
test_old: test_time_insert_old test_time_delete_old test_time_delete2_old test_time_insert2_old test_scan1_old test_scan2_old test_scan3_old

test_time_insert_new: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_time_insert_new.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_time_insert_new.o amscan.o amprint.o -o test_time_insert_new

test_time_insert_old: am_old.o amfns_old.o amsearch_old.o aminsert_old.o amstack_old.o amglobals_old.o ../../pflayer/pflayer.o test_time_insert_old.o amscan_old.o amprint_old.o
	cc -w -g am_old.o amfns_old.o amsearch_old.o aminsert_old.o  amstack_old.o amglobals_old.o ../../pflayer/pflayer.o test_time_insert_old.o amscan_old.o amprint_old.o -o test_time_insert_old

test_time_insert_new.o: test_time_insert.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_time_insert.c -o test_time_insert_new.o

test_time_insert_old.o: test_time_insert.c ../../../toydb/amlayer/am.h ../../../toydb/amlayer/pf.h
	cc -w -g -c test_time_insert.c -o test_time_insert_old.o

test_time_insert2_new: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_time_insert2_new.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_time_insert2_new.o amscan.o amprint.o -o test_time_insert2_new

test_time_insert2_old: am_old.o amfns_old.o amsearch_old.o aminsert_old.o amstack_old.o amglobals_old.o ../../pflayer/pflayer.o test_time_insert2_old.o amscan_old.o amprint_old.o
	cc -w -g am_old.o amfns_old.o amsearch_old.o aminsert_old.o  amstack_old.o amglobals_old.o ../../pflayer/pflayer.o test_time_insert2_old.o amscan_old.o amprint_old.o -o test_time_insert2_old

test_time_insert2_new.o: test_time_insert.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_time_insert2.c -o test_time_insert2_new.o

test_time_insert2_old.o: test_time_insert.c ../../../toydb/amlayer/am.h ../../../toydb/amlayer/pf.h
	cc -w -g -c test_time_insert2.c -o test_time_insert2_old.o




test_time_delete_new: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_time_delete_new.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_time_delete_new.o amscan.o amprint.o -o test_time_delete_new

test_time_delete_new.o: test_time_delete.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_time_delete.c -o test_time_delete_new.o

test_time_delete_old: am_old.o amfns_old.o amsearch_old.o aminsert_old.o amstack_old.o amglobals_old.o ../../pflayer/pflayer.o test_time_delete_old.o amscan_old.o amprint_old.o
	cc -w -g am_old.o amfns_old.o amsearch_old.o aminsert_old.o  amstack_old.o amglobals_old.o ../../pflayer/pflayer.o test_time_delete_old.o amscan_old.o amprint_old.o -o test_time_delete_old

test_time_delete_old.o: test_time_delete.c ../../../toydb/amlayer/am.h ../../../toydb/amlayer/pf.h
	cc -w -g -c test_time_delete.c -o test_time_delete_old.o


test_time_delete2_new: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_time_delete2_new.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_time_delete2_new.o amscan.o amprint.o -o test_time_delete2_new

test_time_delete2_new.o: test_time_delete.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_time_delete2.c -o test_time_delete2_new.o

test_time_delete2_old: am_old.o amfns_old.o amsearch_old.o aminsert_old.o amstack_old.o amglobals_old.o ../../pflayer/pflayer.o test_time_delete2_old.o amscan_old.o amprint_old.o
	cc -w -g am_old.o amfns_old.o amsearch_old.o aminsert_old.o  amstack_old.o amglobals_old.o ../../pflayer/pflayer.o test_time_delete2_old.o amscan_old.o amprint_old.o -o test_time_delete2_old

test_time_delete2_old.o: test_time_delete.c ../../../toydb/amlayer/am.h ../../../toydb/amlayer/pf.h
	cc -w -g -c test_time_delete2.c -o test_time_delete2_old.o


test_scan1_new: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan1_new.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan1_new.o amscan.o amprint.o -o test_scan1_new

test_scan1_new.o: test_scan1.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan1.c -o test_scan1_new.o

test_scan1_old: am_old.o amfns_old.o amsearch_old.o aminsert_old.o amstack_old.o amglobals_old.o ../../pflayer/pflayer.o test_scan1_old.o amscan_old.o amprint_old.o
	cc -w -g am_old.o amfns_old.o amsearch_old.o aminsert_old.o  amstack_old.o amglobals_old.o ../../pflayer/pflayer.o test_scan1_old.o amscan_old.o amprint_old.o -o test_scan1_old

test_scan1_old.o: test_scan1.c ../../../toydb/amlayer/am.h ../../../toydb/amlayer/pf.h
	cc -w -g -c test_scan1.c -o test_scan1_old.o


test_scan2_new: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan2_new.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan2_new.o amscan.o amprint.o -o test_scan2_new

test_scan2_new.o: test_scan2.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan2.c -o test_scan2_new.o

test_scan2_old: am_old.o amfns_old.o amsearch_old.o aminsert_old.o amstack_old.o amglobals_old.o ../../pflayer/pflayer.o test_scan2_old.o amscan_old.o amprint_old.o
	cc -w -g am_old.o amfns_old.o amsearch_old.o aminsert_old.o  amstack_old.o amglobals_old.o ../../pflayer/pflayer.o test_scan2_old.o amscan_old.o amprint_old.o -o test_scan2_old

test_scan2_old.o: test_scan2.c ../../../toydb/amlayer/am.h ../../../toydb/amlayer/pf.h
	cc -w -g -c test_scan2.c -o test_scan2_old.o

test_scan3_new: am.o amfns.o amsearch.o aminsert.o amstack.o amglobals.o ../../pflayer/pflayer.o test_scan3_new.o amscan.o amprint.o
	cc -w -g am.o amfns.o amsearch.o aminsert.o  amstack.o amglobals.o ../../pflayer/pflayer.o test_scan3_new.o amscan.o amprint.o -o test_scan3_new

test_scan3_new.o: test_scan3.c ../../amlayer/am.h ../../amlayer/pf.h
	cc -w -g -c test_scan3.c -o test_scan3_new.o

test_scan3_old: am_old.o amfns_old.o amsearch_old.o aminsert_old.o amstack_old.o amglobals_old.o ../../pflayer/pflayer.o test_scan3_old.o amscan_old.o amprint_old.o
	cc -w -g am_old.o amfns_old.o amsearch_old.o aminsert_old.o  amstack_old.o amglobals_old.o ../../pflayer/pflayer.o test_scan3_old.o amscan_old.o amprint_old.o -o test_scan3_old

test_scan3_old.o: test_scan3.c ../../../toydb/amlayer/am.h ../../../toydb/amlayer/pf.h
	cc -w -g -c test_scan3.c -o test_scan3_old.o

clean: 
	@rm -f *.o
	@rm -f *.out
	@rm -f *~
	@rm -f testrel.*
	@rm -f test_time_delete_old test_time_delete_new test_time_delete2_new test_time_insert_old test_time_insert_new test_time_insert2_new test_time_insert2_old test_time_delete2_old
	@rm -f test_scan1_old test_scan3_old test_scan3_new test_scan1_new test_scan2_old test_scan2_new