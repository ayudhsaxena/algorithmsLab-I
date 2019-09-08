#include <stdio.h>
#include <stdlib.h>

typedef struct n{
  char tok;
  struct n *next;
}node;

typedef struct s{
  node* top;
}stack;

int isEmpty(stack* stack);
stack* createStack();
char peep(stack* stack);
char pop(stack* stack);
void push(stack* stack,char op);
int isOperand(char ch);
int precedence(char op1,char op2);
int isOperator(char ch);
void printStack(stack* stack);
  
int main()
{
  FILE *fi,*fo;
  char ch;
  int num;
  fi=fopen("input.txt","r");
  fo=fopen("18CS10007_A2_P1_output.txt","w");
  stack *stack=createStack();
  while(1)
    {
      while((ch=fgetc(fi))!='\n' && ch!=EOF)
	   {
        printf("Currect tok =%c\n",ch);
        printf("The stack at the start of each iteration :\n");
        printStack(stack);
    	  if(isOperand(ch))
    	    {
            ungetc(ch,fi);
            fscanf(fi,"%d",&num);
            fprintf(fo,"%d ",num);
          }
    	  else if(isOperator(ch))
    	    {
    	      while(!isEmpty(stack) &&  stack->top->tok != '(' && precedence(ch,stack->top->tok))
      		{
      		  fprintf(fo,"%c ",pop(stack));
      		}
  	      push(stack,ch);
    	    }  
    	  else if(ch=='(')
    	    {
    	      push(stack,ch);
    	    }
    	  else
    	    {
    	      if(stack->top->tok != '(')
          		{
          		  fprintf(fo,"%c ",pop(stack));
          		}
    	      pop(stack);
    	    }
    	}
      
    while(!isEmpty(stack))
        {
          fprintf(fo,"%c ",pop(stack));
        }
      
    fprintf(fo,"\n");

    //break;

    if(ch==EOF)
	    break;
    }
}


stack* createStack()
{
  stack *s;
  s=(stack*)malloc(sizeof(stack));
  s->top=NULL;
  return s;
}

int isEmpty(stack* stack)
{
  if(stack->top==NULL)
    return 1;
  else
    return 0;
}

char peep(stack* stack)
{
  return stack->top->tok;
}

char pop(stack* stack)
{
  char c;
  node *p;
  p=stack->top;
  stack->top=stack->top->next;
  c=p->tok;
  free(p);
  return c;
}

void push(stack* stack,char op)
{
  node *p;
  p=(node*)malloc(sizeof(node));
  p->next=stack->top;
  stack->top=p;
  p->tok=op;
}

int isOperand(char ch)
{
  switch(ch)
    {
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': return 1;
      
    default : return 0;
    }
}

int isOperator(char ch)
{
  switch(ch)
    {
    case '*':  case '/':  case '%':  case '+':  case '-': return 1;
    default : return 0;
    }
}

int precedence(char op1,char op2)
{
  int p1,p2;
  switch(op1)
    {
    case '(' : case ')' : p1=3; break;
    case '*' : case '%' : case '/' : p1=2; break;
    case '+' : case '-' : p1=1; break;
    }
  switch(op2)
    {
    case '(' : case ')' : p2=3; break;
    case '*' : case '%' : case '/' : p2=2; break;
    case '+' : case '-' : p2=1; break;
    }
  if(p2>=p1)
    return 1;
  else
    return 0;
}
 
void printStack(stack* stack)
{
  node *p;
  p=stack->top;
  if(!p)
    {
      printf("No elements in stack!\n");
    }
    else
    {
       while(p)
      {
        printf("%c\n",p->tok);
        p=p->next;
      }
    }
}