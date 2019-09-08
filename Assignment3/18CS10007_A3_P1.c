/* Name : Ayudh Saxena
   Roll no : 18CS10007 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int Max_Cross_Seg(int S[],int low,int mid,int high);
int Max_Seg(int S[],int low,int high);

int main()
{
	FILE *fi;
	int n,*S;

	fi=fopen("input.txt","r");
	fscanf(fi,"%d",&n);
	S=(int*)malloc(n*sizeof(int));
	
	for(int i=0;i<n;i++)  //reading the array S from file
	{
		fscanf(fi,"%d",&S[i]);
	}
	printf("%d\n",Max_Seg(S,0,n-1));
}

int Max_Cross_Seg(int S[],int low,int mid,int high)
{
	int left_sum,right_sum,sum=0;
	left_sum = right_sum = -INFINITY;

	for(int i = mid;i >= low;i--)  //maximum sum of subarray contained in from mid to low and starting from mid
	{
		sum += S[i];
		if(sum > left_sum)
		{
			left_sum = sum;
		}
	}

	sum=0;
	for(int i=mid+1;i<=high;i++) //maximum sum of subarray contained in from mid+1 to high and starting from mid+1
	{
		sum += S[i];
		if(sum > right_sum)
		{
			right_sum = sum;
		}
	}
	return (left_sum + right_sum);
}

int Max_Seg(int S[],int low,int high)
{
	int left_seg_max, right_seg_max, cross_seg_max, mid;
	mid = (low+high)/2;
	if(low == high)
	{
		return S[low]; //base case
	}
	else
	{
		left_seg_max = Max_Seg(S,low,mid);		//divide
		right_seg_max = Max_Seg(S,mid+1,high);	
		cross_seg_max = Max_Cross_Seg(S,low,mid,high); //subarray contained in both the halves
	}

	/*getting maximum of the three*/
	if(left_seg_max >= right_seg_max && left_seg_max >= cross_seg_max)
	{
		return left_seg_max;
	}
	else if(right_seg_max >= left_seg_max && right_seg_max >= cross_seg_max)
	{
		return right_seg_max;
	}
	else
	{
		return cross_seg_max;
	}
}

