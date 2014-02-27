#include <stdio.h>
#include "../../amlayer/am.h"
#include "../../amlayer/pf.h"
#include "../../amlayer/testam.h"

#define MAXRECS	200	/* max # of records to insert */
#define FNAME_LENGTH 80	/* file name size */

main()
{
int fd;	/* file descriptor for the index */
char fname[FNAME_LENGTH];	/* file name */
int recnum;	/* record number */
int sd;	/* scan descriptor */
int numrec;	/* # of records retrieved */
int testval;	

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

	printf("Inserting into index all record IDs from 500-2500 with attribute values 0-2000\n");
	for (recnum=500; recnum < 2501; recnum++){
		int value = (recnum-500);
		AM_InsertEntry(fd,INT_TYPE,sizeof(int),(char *)&value,
				recnum);
	}

	printf("Now we delete all the record IDs which are divisible by 2\n");
	for(recnum=500; recnum<2501;recnum+=2){
		int value = (recnum-500);
		AM_DeleteEntry(fd,INT_TYPE, sizeof(int),(char*)&value,recnum);
	}

	printf("Print all the remaining elements to check if AM_DeleteEntry works properly (the number of printed recIDs should be 1000)\n");
	numrec= 0;
	sd = AM_OpenIndexScan(fd,INT_TYPE,sizeof(int),EQ_OP,NULL);
	while((recnum=AM_FindNextEntry(sd))>= 0){
		printf("%d, ",recnum);
		numrec++;
	}
	printf("\n\nretrieved %d records\n",numrec);
	AM_CloseIndexScan(sd);

	printf("closing down\n");
	PF_CloseFile(fd);
	AM_DestroyIndex(RELNAME,0);

	printf("Testing delete done");
}