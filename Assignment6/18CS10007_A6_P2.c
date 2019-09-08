#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX 500

typedef struct _treenode {
char * route ;
struct _treenode * left ;
struct _treenode * right ;
int height;
} AVLtreenode ;

typedef AVLtreenode* AVLtree ;	

char* filterRoute(char *r);
int max(int a,int b);
int height(AVLtree root);
AVLtree leaf(char *r);
AVLtree rotateRight(AVLtree root);
AVLtree rotateLeft(AVLtree root);
AVLtree insertAVL(AVLtree root,char *r);
AVLtree rebalance(AVLtree root);
void inOrder(AVLtree root,FILE *fo);
AVLtree search(AVLtree root,char *r);
void preOrder(AVLtree root);
char* deleteCharMultiple(char *s,int pos);
char* deletePlanet(AVLtree root,char *r);
char* addPlanet(AVLtree root,char *r);
char* deleteCharSingle(char *s,int pos);
void HAL9001(AVLtree root,FILE *fi,FILE *fo);


int main()
{
	FILE *fi;
	int n;
	char r[MAX];
	AVLtree root = NULL;
	fi = fopen("Routes.txt","r");
	fscanf(fi,"%d",&n);
	for (int i = 0; i < n; ++i)
	{
		fscanf(fi,"%s",r);
		if(search(root,r) == NULL)
			root = insertAVL(root,filterRoute(r));
	}
	HAL9001(root,fopen("Query.txt","r"),fopen("18CS10007_A6_output.txt","a"));
}	

char* filterRoute(char *r)
{
	int i = 0,j;
	while(r[i] != '\0')
	{
		if(r[i] == r[i+1])
		{
			j = i;
			while(r[j] != '\0')
			{
				r[j] = r[j+1];
				j++;
			}
			i--;
		}
		i++;
	}
	return r;
}

AVLtree insertAVL(AVLtree root,char *r)
{
	AVLtree T;
	T = root;
	if(T == NULL)
		T = leaf(r);
	else if(strcmp(r,T->route) < 0)
		T->left = insertAVL(T->left,r);
	else
		T->right = insertAVL(T->right,r);

	T->height = 1 + max(height(T->left),height(T->right));

	T = rebalance(T);

	return T;
}

AVLtree rebalance(AVLtree root)
{
	AVLtree r,l;
	r = root->right;
	l = root->left;
	int hr = height(r);
	int hl = height(l);
	if(hr > hl+1)
	{
		if(height(r->right) > height(r->left))
			root = rotateLeft(root);
		else
		{
			root->right = rotateRight(root->right);
			root = rotateLeft(root);
		}
	}
	else if(hl > hr+1)
	{
		if(height(l->left) > height(l->right))
			root = rotateRight(root);
		else
		{
			root->left = rotateLeft(root->left);
			root = rotateRight(root);
		}
	}

	return root;
}

AVLtree rotateLeft(AVLtree root)
{
	

	AVLtree t = root->right;
	root->right = t->left;
	t->left = root;

	root->height = 1 + max(height(root->left),height(root->right));
	t->height = 1 + max(height(t->left),height(t->right));
	
	return t;
}

AVLtree rotateRight(AVLtree root)
{
	AVLtree t = root->left;
	root->left = t->right;
	t->right = root;
	
	root->height = 1 + max(height(root->left),height(root->right));
	t->height = 1 + max(height(t->left),height(t->right));
	
	return t;
}

AVLtree leaf(char *r)
{
	AVLtree t;
	t = (AVLtree)malloc(sizeof(AVLtreenode));
	t->route = (char*)malloc((strlen(r)+1)*sizeof(char));
	strcpy(t->route,r);
	t->right = NULL;
	t->left = NULL;
	t->height = 1;

	return t;
}

int max(int a,int b)
{
	return a > b ? a : b;
}

int height(AVLtree root)
{
	return root == NULL ? 0 : root->height;
}

void inOrder(AVLtree root,FILE *fo)
{
	if(root)
	{
		inOrder(root->left,fo);
		fprintf(fo,"%s\n",root->route);
		inOrder(root->right,fo);
	}
}

AVLtree search(AVLtree root,char *r)
{
	if(root == NULL)
		return NULL;
	else if(strcmp(r,root->route) == 0)
		return root;
	else if(strcmp(r,root->route) < 0)
		return search(root->left,r);
	else
		return search(root->right,r);
}

void preOrder(AVLtree root)
{
	if(root)
	{
		printf("%s\n",root->route);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void HAL9001(AVLtree root,FILE *fi,FILE *fo)
{
	int n;
	char r[MAX];
	fscanf(fi,"%d",&n);
	for (int i = 0; i < n; ++i)
	{
		fscanf(fi,"%s",r);
		fprintf(fo,"Corrections for the root \"%s\": %s\n",r,filterRoute(r));
		if(search(root,r) == NULL)
		{
			fprintf(fo,"Searching for the route \"%s\": Not found\n",r);
			fprintf(fo,"Alternate route suggestion :\n");
			fprintf(fo,"Rule 1 :");
			if(addPlanet(root,r) != NULL)
				fprintf(fo,"%s",addPlanet(root,r));
			fprintf(fo,"\nRule 2 :");
			if(deletePlanet(root,r) != NULL)
				fprintf(fo,"%s",deletePlanet(root,r));
		}
		else
			fprintf(fo,"Searching for the route \"%s\": Found",r);
		fprintf(fo,"\n\n");
		}
	
}

char* addPlanet(AVLtree root,char *r) //checks if any deletion permutation of the existing routes in the tree matches the input route
{
	int i=0;
	char *s;
	if(root)
	{
		s = addPlanet(root->left,r);
		if(s)
			return s;

		while(root->route[i] != '\0')
		{
			if(strcmp(r,deleteCharSingle(root->route,i)) == 0)
				return root->route;
			i++;
		}

		s = addPlanet(root->right,r);
		if(s)
			return s;
	}

	return NULL;
}

char* deletePlanet(AVLtree root,char *r) //searches all the single character deletion permutation of the input route
{
	int i=0;
	if(root)
	{
		while(r[i] != '\0')
		{
			if(search(root,deleteCharMultiple(r,i)) != NULL)
				return deleteCharMultiple(r,i);
			i++;
		}
	}
	
	return NULL;
}

char* deleteCharMultiple(char *s,int pos) //delete all the occurrences of a single character, the input position defines that character
{                                               
	char *new;
	int i =0,j=0;
	new = (char*)malloc(strlen(s)*sizeof(char));
	while(s[j] != '\0')
	{
		if(s[j]!=s[pos])
		{
			new[i] = s[j];
			i++;
		}
		j++;
	}
	new[i] = '\0';
	return new;
}

char* deleteCharSingle(char *s,int pos) //delete only a single character, the character at the input position
{
	char *new;
	int i =0,j=0;
	new = (char*)malloc(strlen(s)*sizeof(char));
	while(s[j] != '\0')
	{
		if(j != pos)
		{
			new[i] = s[j];
			i++;
		}
		j++;
	}
	new[i] = '\0';
	return new;
}
