#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int bestWorstCase(int k,int n);
int max(int a,int b);

int main()
{
	printf("%d\n",bestWorstCase(4,15));
}

int bestWorstCase(int k,int n)
{
	/*Base Cases :
	bestWorstCase(1,n) = n;
	bestWorstCase(k,0) = 0;*/

	/*Recurrence Relation :
	 bestWorstCase(k,n) = min(max(bestWorstCase(k-1,i-1),bestWorstCase(k,n-i))) where i varies from 1 to n*/


	/*Explanantion :
	Starting with k test tubes,whenever a venom dissolves in a test tube, our interest of consideration shifts to 
	the rest of the test tubes to the left of it with remaining k-1 capsules and if it doesn't dissolve our interest of 
	consideration shifts to the rest of the test tubes to the right of it with all the k capsules still in tact.
	To get the best of worst cases, we'll evaulate all the worst cases and choose the best from it.Furthermore
	these worst cases will in fact stem from the worst of the sub best worst cases(because we have to calculate
	the worst case we're choosing the worst case and not the best of the sub best worst cases).So when we start
	from a given test tube we will recursively call the bestWorstCase function to get the best worst case for the test tubes 
	to the left of the selected test tube and best worst case for the test tubes to the right of it and hence choose the worst of
	these cases.Since our starting test tube can vary from the 1st test tube to the nth test tube, we will do this procedure n times.
	Now that we have got all the possible worst cases we will choose the best of from it and 1+(the best case) will be our answer.*/

	if(k == 1 || n == 0)
		return n;	
			else 
			{
				int min = INFINITY,maxm;
				for (int i = 1; i <= n; ++i)
				{
					maxm = max(bestWorstCase(k-1,i-1),bestWorstCase(k,n-i));
					if(maxm < min)
						min = maxm;
				}
				return min+1;
			}
}

int max(int a,int b)
{
	return a > b ? a : b;
}