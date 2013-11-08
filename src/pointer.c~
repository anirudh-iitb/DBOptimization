#include <stdio.h>

int main()
{
	char* pageBuf;
	char* valBuf;
	
	int attrLength = sizeof(int)+sizeof(int);
	
	int attr = 4;
	int value = 4;
	
	int recId1 = 7;
	int recId2 = 7;
	
	pageBuf = &attr;
	valBuf = &value;
	
	bcopy((char*)&recId1, pageBuf+sizeof(int),sizeof(int));
	bcopy((char*)&recId2, valBuf+sizeof(int),sizeof(int));
	
	int x = strncmp(valBuf,pageBuf,attrLength);
	printf("%02x\n",pageBuf);
	return 0;
}
