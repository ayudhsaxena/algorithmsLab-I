#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int bestWorstCase(int k, int n);
int max(int a,int b);

int main()
{
	FILE *fi,*fo;
	int q,k,n;
	fi = fopen("input.txt","r");
	fo = fopen("output.txt","w");
	fscanf(fi,"%d",&q);
	for (int i = 0; i < q; ++i)
	{
		fscanf(fi,"%d %d",&k,&n);
		fprintf(fo,"%d %d %d\n",k,n,bestWorstCase(k,n));
	}
}

int bestWorstCase(int k, int n)
{
	int **w;
	w = (int**)malloc(k*sizeof(int*));
	for (int i = 0; i < k; ++i)
	{
		w[i] = (int*)malloc((n+1)*sizeof(int));
	}

	for (int i = 0; i < k; ++i)
	{
		for(int j = 0; j < n+1; j++)
		{
			if(i == 0 || j == 0)
				w[i][j] = j;
			else
			{
				int min = INFINITY,maxm;
				for (int m = 1; m <= j; ++m)
				{
					maxm = max(w[i-1][m-1],w[i][j-m]);
					if(maxm < min)
						min = maxm;
				}
				w[i][j] = min +1;
			}
		}
	}
	 return w[k-1][n];

}

int max(int a,int b)
{
	return a > b ? a : b;
};