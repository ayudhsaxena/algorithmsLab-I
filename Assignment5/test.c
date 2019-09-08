#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max(a,b) a > b ? a : b

void lol(int x,int y);
int lol2(int *x);

int main()
{
	char *a;
	a =(char*)calloc(3,sizeof(char));
	a[0] = 'i';
	int x=3;
	lol(lol2(&x),lol2(&x));
}

void lol(int x,int y)
{
	printf("x = %d y = %d",x,y);
}

int lol2(int *x)
{
	return *x+=1;
}
