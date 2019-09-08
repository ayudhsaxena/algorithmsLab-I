#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *fi,*fo;
  int x;
  fi=fopen("18CS10007_A2_P1_output.txt","r");
  fo=fopen("18CS10007_A2_P2_output.txt","w");
  fscanf(fi,"%d",&x);
  printf("%d",x);
}