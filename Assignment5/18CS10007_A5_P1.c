#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
char symbol ;
int frequency ;
struct node *next ;
struct node *left ;
struct node *right ;
}node;

int main()
{
	FILE *fi,*fo;
	int n;
	char c;
	node arr[36];
	fo = fopen("output.txt","w");
	for (int i = 0; i < 26; ++i)
	{
		arr[i].symbol = 'a'+i;
		arr[i].frequency = 0;
	}
	for (int i = 0; i < 10; ++i)
	{
		arr[26+i].symbol = '0' + i;
		arr[26+i].frequency = 0;
	}
	
	for (int i = 0; i < 36; ++i)
	{
		fi = fopen("log-2.txt","r");
		fscanf(fi,"%d",&n);;
		while((c=fgetc(fi))!=EOF)
		{
			if(c == arr[i].symbol)
				arr[i].frequency++;;
		}
		fprintf(fo,"%c = %d, ",arr[i].symbol,arr[i].frequency);
	}	
}

