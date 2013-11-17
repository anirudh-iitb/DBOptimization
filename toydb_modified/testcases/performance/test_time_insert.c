#include <stdio.h>
#include <time.h>
#include "../../amlayer/am.h"
#include "../../amlayer/pf.h"
#include "../../amlayer/testam.h"

#define MAXRECS 10000
#define FNAME_LENGTH 80

main(){
	int fd;	/* file descriptor for the index */
	char fname[FNAME_LENGTH];	/* file name */
	int recnum;	/* record number */
	int sd;	/* scan descriptor */
	int numrec;	/* # of records retrieved */
	int testval;

	clock_t t;	
	// timeval t1, t2;
	// double elapsedtime;

	/* init */
	printf("initializing\n");
	PF_Init();

	/* create index */
	printf("creating index\n");
	AM_CreateIndex(RELNAME,0,CHAR_TYPE,sizeof(char));

	/* open the index */
	printf("opening index\n");
	sprintf(fname,"%s.0",RELNAME);
	fd = PF_OpenFile(fname);

	t = clock();
	// gettimeofday(&t1,NULL);
	for (recnum=1; recnum < MAXRECS; recnum++){
		char value;
		if(recnum%4==0) value='a';
		else if(recnum%4==1) value='b';
		else if(recnum%4==2) value='c';
		else value='d';
		AM_InsertEntry(fd,CHAR_TYPE,sizeof(char),(char *)&value,
				recnum);
	}
	t = clock()-t;
	// gettimeofday(&t2,NULL);

	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	// elapsedtime = (t2.tv_sec - t1.tv_sec) * 1000.0;
	// elapsedtime += (t2.tv_usec - t1.tv_usec) / 1000.0;

	printf("Insert takes %f seconds to insert records with repeating attributes\n", time_taken);
	printf("Number of pages used %d\n",totalNumberOfPages);
	printf("closing down\n");
	PF_CloseFile(fd);
	AM_DestroyIndex(RELNAME,0);
}
