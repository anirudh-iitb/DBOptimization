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
char testval;	

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

	printf("We test scan by printing all rec IDs with value <= 2850 (number of printed recIDs should be 850)\n");
	int val = 2850;
	int numOfRecords = 0;
	sd = AM_OpenIndexScan(fd,INT_TYPE,sizeof(int),LE_OP,(char *)&val);
	while((recnum=AM_FindNextEntry(sd))>= 0){
		printf("%d, ",recnum);
		numOfRecords++;
	}
	AM_CloseIndexScan(sd);
	printf("\n\nRetrieved %d records\n", numOfRecords);

	printf("closing down\n");
	PF_CloseFile(fd);
	AM_DestroyIndex(RELNAME,0);

	printf("Testing scan's less than or equal to operation done\n");
}