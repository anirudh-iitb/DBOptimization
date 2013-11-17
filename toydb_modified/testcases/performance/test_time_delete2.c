#include <stdio.h>
#include <time.h>
#include "../../amlayer/am.h"
#include "../../amlayer/pf.h"
#include "../../amlayer/testam.h"

#define MAXRECS 1000
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
	AM_CreateIndex(RELNAME,0,INT_TYPE,sizeof(int));

	/* open the index */
	printf("opening index\n");
	sprintf(fname,"%s.0",RELNAME);
	fd = PF_OpenFile(fname);
	int value = 1;
	for (recnum=0; recnum < MAXRECS; recnum++){
		AM_InsertEntry(fd,INT_TYPE,sizeof(int),(char *)&recnum,
				recnum);
	}
	t = clock();
	for(recnum=0;recnum < MAXRECS; recnum++){
		AM_DeleteEntry(fd,INT_TYPE,sizeof(int),(char*)&recnum,recnum);
	}
	t = clock()-t;

	double time_taken = ((double)t)/CLOCKS_PER_SEC;

	printf("Delete takes %f seconds to delete records\n", time_taken);
	printf("Number of pages used %d\n",totalNumberOfPages);
	printf("closing down\n");
	PF_CloseFile(fd);
	AM_DestroyIndex(RELNAME,0);
}
