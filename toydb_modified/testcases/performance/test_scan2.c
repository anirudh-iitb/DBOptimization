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

	// gettime
	for (recnum=1; recnum < MAXRECS; recnum++){
		char value;
		if(recnum%4==0) value='a';
		else if(recnum%4==1) value='b';
		else if(recnum%4==2) value='c';
		else value='d';
		AM_InsertEntry(fd,CHAR_TYPE,sizeof(char),(char *)&value,
				recnum);
	}
	// gettimeofday(&t2,NULL);
	
	t = clock();
	numrec= 0;
	char val = 'b';
	sd = AM_OpenIndexScan(fd,CHAR_TYPE,sizeof(char),GT_OP,&val);
	while((recnum=AM_FindNextEntry(sd))>= 0){
		numrec++;
	}
	AM_CloseIndexScan(sd);
	t = clock()-t;



	double time_taken = ((double)t)/CLOCKS_PER_SEC;

	printf("Scan takes %f seconds to retreive records with repeating attributes\n", time_taken);
	printf("Number of pages used %d\n",totalNumberOfPages);
	printf("closing down\n");
	PF_CloseFile(fd);
	AM_DestroyIndex(RELNAME,0);
}