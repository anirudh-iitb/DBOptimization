#include <stdio.h>
#include "am.h"
#include "pf.h"
#include "testam.h"

#define MAXRECS	1500	/* max # of records to insert */
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

	printf("inserting into index\n");
	for (recnum=0; recnum < MAXRECS; recnum++){
		// printf("Inserting %d\n",recnum);
		int value = recnum+1000;
		AM_InsertEntry(fd,INT_TYPE,sizeof(int),(char *)&value,
				recnum);
	}

	numrec= 0;
	int value=1200;
	// sd = AM_OpenIndexScan(fd,INT_TYPE,sizeof(int),EQ_OP,(char*)&value);
	// while((recnum=AM_FindNextEntry(sd))>= 0){
	// 	int x = AM_DeleteEntry(fd,INT_TYPE,sizeof(int),(char *)&value,
	//  				recnum);
	//  	// printf("%d %d\n",x, recnum);	
	// }
	// AM_CloseIndexScan(sd);

	// printf("printing all values\n");
	numrec= 0;
	sd = AM_OpenIndexScan(fd,INT_TYPE,sizeof(int),EQ_OP,(char*)&value);
	while((recnum=AM_FindNextEntry(sd))>= 0){
		printf("%d\n",recnum);
		numrec++;
	}
	printf("retrieved %d records\n",numrec);
	AM_CloseIndexScan(sd);

	printf("closing down\n");
	PF_CloseFile(fd);
	AM_DestroyIndex(RELNAME,0);
}