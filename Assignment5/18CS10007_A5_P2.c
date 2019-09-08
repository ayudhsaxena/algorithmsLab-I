#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct node{
char *symbol ;
int frequency ;
struct node *next ;
struct node *left ;
struct node *right ;
}node;

node* insert(node* head,node v);
node* modify(node* head,int i);
int newCompare(char *a,char *b);
void preOrder(node* T);

int main()
{
	FILE *fi,*fo;
	int n;
	char c;
	node arr[36];
	fo = fopen("lol.txt","w");
	for (int i = 0; i < 26; ++i)
	{
		arr[i].symbol = (char*)calloc(2,sizeof(char));
		arr[i].symbol[0] = 'a'+i;
		arr[i].frequency = 0;
		arr[i].next = NULL;
		arr[i].left = NULL;
		arr[i].right = NULL;
	}
	for (int i = 0; i < 10; ++i)
	{
		arr[26+i].symbol = (char*)calloc(2,sizeof(char));
		arr[26+i].symbol[0] = '0' + i;
		arr[26+i].frequency = 0;
		arr[26+i].next = NULL;
		arr[26+i].left = NULL;
		arr[26+i].right = NULL;

	}
	
	for (int i = 0; i < 36; ++i)
	{
		fi = fopen("log-2.txt","r");
		fscanf(fi,"%d",&n);;
		while((c=fgetc(fi))!=EOF)
		{
			if(c == arr[i].symbol[0])
				arr[i].frequency++;;
		}
		fprintf(fo,"%c = %d ,",arr[i].symbol[0],arr[i].frequency);
	}

	/*P A R T 2*/

	node *head = NULL,*ptr;

	for (int i = 0; i < 36; ++i)
	{
		head = insert(head,arr[i]);
	}

	for (int i = 1; i < 36; ++i)
	{
		head = modify(head,i);
		ptr = head;
	while(ptr)
	{
		printf("%s = %d\n",ptr->symbol,ptr->frequency);
		ptr = ptr->next;
	}
	printf("\n\n");	
	}
	
	ptr = head;
	while(ptr)
	{
		printf("%s = %d\n",ptr->symbol,ptr->frequency);
		ptr = ptr->next;
	}	

	preOrder(head);
}

node* insert(node* head,node v)
{
	node *new,*ptr1,*ptr2;
	new = (node*)malloc(sizeof(node));
	*new = v;
	ptr1 = head;
	ptr2 = ptr1;
	while(ptr1 != NULL && ptr1->frequency < new->frequency)
	{
		ptr2 = ptr1;
		ptr1 = ptr1->next;
	}
	while(ptr1 != NULL && ptr1->frequency <= new->frequency && newCompare(ptr1->symbol,new->symbol) < 0)
	{
		ptr2 = ptr1;
		ptr1 = ptr1->next;
	}
	

	if(ptr1 == head)
	{
		new->next = ptr1;
		head = new;
	}
	else
	{
		ptr2->next = new;
		new->next = ptr1;
	}

	return head;
}

node* modify(node* head,int i)
{
	node *new,*ptr1,*ptr2;
	ptr2 = head;
	ptr1 = ptr2->next;
	new = (node*)malloc(sizeof(node));
	new->symbol = (char*)calloc(4,sizeof(char));
	sprintf(new->symbol,"N%d",i);
	new->frequency = ptr2->frequency + ptr1->frequency;
	if(newCompare(ptr2->symbol,ptr1->symbol) < 0)
	{
		new->left = ptr2;
		new->right = ptr1;
	}
	else
	{
		new->left = ptr1;
		new->right = ptr2;
	}
	head = ptr1->next;
	head = insert(head,*new);
	return head;
}

int newCompare(char *a,char *b)
{
	if(strlen(a) == strlen(b))
		return strcmp(a,b);
	else if(a[0] == b[0])
		{
			if(strlen(a) < strlen(b))
				return -1;
			else
				return 1;
		}
	else
	{
		if(a[0] == 'N')
			return -1;
		else
			return 1;
	}
		
}

void preOrder(node* T)
{
	if(T!=NULL)
	{
		printf("%s,",T->symbol);
		preOrder(T->left);
		preOrder(T->right);
	}
}