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
	AM_CreateIndex(RELNAME,0,CHAR_TYPE,sizeof(char));

	/* open the index */
	printf("opening index\n");
	sprintf(fname,"%s.0",RELNAME);
	fd = PF_OpenFile(fname);

	printf("Inserting into index record IDs 1-1000 with attribute value 'a' for (recID)mod3=0, 'b' for (recID)mod3=1 and 'c'for (recID)mod3=2\n");
	for (recnum=1; recnum < 1001; recnum++){
		char value;
		if(recnum%3==0) value='a';
		else if(recnum%3==1) value='b';
		else value='c';
		AM_InsertEntry(fd,CHAR_TYPE,sizeof(char),(char *)&value,
				recnum);
	}

	printf("We test scan by printing all the elements with attribute value less than 'b'(the number of printed recIDs should be 333)\n");
	numrec= 0;
	char val = 'b';
	sd = AM_OpenIndexScan(fd,CHAR_TYPE,sizeof(char),LT_OP,&val);
	while((recnum=AM_FindNextEntry(sd))>= 0){
		printf("%d, ",recnum);
		numrec++;
	}
	printf("\n\nretrieved %d records\n",numrec);
	AM_CloseIndexScan(sd);

	printf("closing down\n");
	PF_CloseFile(fd);
	AM_DestroyIndex(RELNAME,0);

	printf("Testing scan's less than operation done\n");
}