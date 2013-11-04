#include <stdio.h>

int main()
{
    int *p;
    int a = 4;
    p=&a;
    int recId = 0;
    bcopy(&recId,p+sizeof(int),sizeof(int));
   	char r;
   	bcopy(p,&r,sizeof(int)+sizeof(int));
   	int b;
   	bcopy(&r,&b,sizeof(int));
   	printf("%d\n",b);
    return 0;
}
