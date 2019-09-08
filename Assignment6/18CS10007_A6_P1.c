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

int main()
{
	FILE *fi,*fo;
	int n;
	char r[MAX];
	AVLtree root = NULL;
	fi = fopen("Routes.txt","r");
	fo = fopen("18CS10007_A6_output.txt","w");
	fscanf(fi,"%d",&n);
	for (int i = 0; i < n; ++i)
	{
		fscanf(fi,"%s",r);
		if(search(root,r) == NULL)
			root = insertAVL(root,filterRoute(r));
	}
	fprintf(fo,"%d\n",root->height);
	inOrder(root,fo);
	
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
				r[j] = r[j+1];  //shifting the characters to absorb the repeated characters
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

	T->height = 1 + max(height(T->left),height(T->right)); //updating the heights after addition of the leaf

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

AVLtree leaf(char *r) //addition of leaf to AVL tree
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