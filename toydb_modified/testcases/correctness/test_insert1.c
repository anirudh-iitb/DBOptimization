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

	printf("Inserting into index record IDs 1-1000 with attribute values 2001-3000\n");
	for (recnum=1; recnum < 1001; recnum++){
		int value = (2000+recnum);
		AM_InsertEntry(fd,INT_TYPE,sizeof(int),(char *)&value,
				recnum);
	}

	printf("Now we print all the elements in the index to check whether insertion has been successful\n");
	numrec= 0;
	sd = AM_OpenIndexScan(fd,INT_TYPE,sizeof(int),EQ_OP,NULL);
	while((recnum=AM_FindNextEntry(sd))>= 0){
		printf("%d, ",recnum);
		numrec++;
	}
	printf("\n\nretrieved %d records\n",numrec);
	AM_CloseIndexScan(sd);

	printf("Now we check how many records are present with key value greater than 2500 (answer should be 500)\n");
	testval = 2500;
	int numOfRecords = 0;
	sd = AM_OpenIndexScan(fd,INT_TYPE,sizeof(int),GT_OP,(char *)&testval);
	while((recnum=AM_FindNextEntry(sd))>= 0){
		numOfRecords++;
	}
	AM_CloseIndexScan(sd);
	printf("\nRetrieved %d records\n", numOfRecords);

	printf("closing down\n");
	PF_CloseFile(fd);
	AM_DestroyIndex(RELNAME,0);

	printf("Testing insert done\n");
}