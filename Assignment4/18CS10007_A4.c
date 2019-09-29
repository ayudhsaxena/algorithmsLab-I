#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
	int vertex;
	struct node* next;
}node;

typedef struct graph{
	int numVertices;
	node** adjLists;
}graph;

typedef struct{
	int from;
	int to;
	int weight;
}Edge;

graph createGraph(int V);
void addEdge(graph g,int from,int to);
void printGraph(graph g);
int InDegree(graph g,int v);
Edge* createArrayEdge(graph g,int E);
void printEdges(Edge *arr,FILE *fo,int e);
void mergesort(Edge *arr,int l,int r);
void merge(Edge* arr,int l,int mid,int r);

int main()
{
	FILE *fi,*fo;
	int v,e,from,to;
	graph g;
	Edge *arr;

	fi = fopen("input.txt","r");
	fo = fopen("18CS10007_A4_output.txt","w");
	fscanf(fi,"%d",&v);
	fscanf(fi,"%d",&e);

	g = createGraph(v);
	
	for (int i = 0; i < e; ++i)
	{
		fscanf(fi,"%d %d",&from,&to);
		addEdge(g,from,to);
	}

	arr = createArrayEdge(g,e);
	mergesort(arr,0,e-1);
	printEdges(arr,fo,e);
}

graph createGraph(int V)
{
	graph g;
	g.numVertices = V;
	g.adjLists = (node**)malloc(V*sizeof(node*));

	for (int i = 0; i < V; ++i)
		(g.adjLists[i]) = NULL ;
	
	return g;
}

void addEdge(graph g,int from,int to)
{
	node *new;
	new = (node*)malloc(sizeof(node));
	new->next = g.adjLists[from-1]; 
	g.adjLists[from-1] = new; // adding at the head
	new->vertex = to;
}

void printGraph(graph g)
{
	node* ptr;
	for (int i = 0 ; i < g.numVertices; ++i)
	{
		printf("%d",i+1);
		ptr = g.adjLists[i];
		while(ptr)
		{
			printf("->%d",ptr->vertex);
			ptr = ptr->next;
		}
		printf("\n");
	}
}

Edge* createArrayEdge(graph g,int E)
{
	node* ptr;
	Edge *arr;
	int j=0;
	arr = (Edge*)malloc(E*sizeof(Edge));
	for (int i = 0; i < g.numVertices ; ++i)
	{
		ptr = g.adjLists[i];
		while(ptr)
		{
			arr[j].from = i+1;
			arr[j].to = ptr->vertex;
			arr[j].weight = InDegree(g,arr[j].from) + InDegree(g,arr[j].to);
			ptr = ptr->next;
			j++	;
		}
	}	
	return arr;
}

int InDegree(graph g,int v)
{
	node *ptr;
	int count = 0;
	for (int i = 0; i < g.numVertices ; ++i)
	{
		ptr = g.adjLists[i];
		while(ptr)
		{
			if(ptr->vertex == v) // if v exists in some adjacency list of some vertex
			{
				count++;
			}
			ptr = ptr->next;
		}
	}	
	return count;
}

void printEdges(Edge *arr,FILE *fo,int e)
{
	for (int i = 0; i < e; ++i)
		fprintf(fo, "%d %d %d\n",arr[i].from,arr[i].weight,arr[i].to);
}

void mergesort(Edge *arr,int l,int r)
{
	int mid = (l+r)/2;
	if(l==r)
	{
		return;
	}
	else
	{
		mergesort(arr,l,mid);
		mergesort(arr,mid+1,r);
		merge(arr,l,mid,r);
	}
}

void merge(Edge* arr,int l,int mid,int r)
{
	Edge *v,*u;
	int n1 = mid-l+2, n2 = r-mid+1;
	u = (Edge*)malloc(n1*sizeof(Edge));
	v = (Edge*)malloc(n2*sizeof(Edge));

	for (int i = 0; i < n1-1; ++i)
		u[i] = arr[l+i];
	u[n1-1].from = INFINITY; //to let the remaining other array be copied, indicates the array has no other elements to be copied

	for (int i = 0; i < n2-1; ++i)
		v[i] = arr[mid+1+i];
	v[n2-1].from = INFINITY;

	int i=0,j=0,k=l;
	while(k<=r)
	{
		if(u[i].from == v[j].from)
		{
			if(u[i].weight == v[j].weight)
			{
				if(u[i].to < v[j].to)
				{
					arr[k++] = u[i++];
				}
				else
				{
					arr[k++] = v[j++];
				}
			}
			else if(u[i].weight < v[j].weight)
			{
				arr[k++] = u[i++];
			}
			else
			{
				arr[k++] = v[j++];
			}
		}
		else if( u[i].from < v[j].from)
		{
			arr[k++] = u[i++];
		}
		else
		{
			arr[k++] = v[j++];
		}
	}
}