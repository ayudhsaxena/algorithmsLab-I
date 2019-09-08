#include <stdio.h>
#include <stdlib.h>

typedef struct n{
  int tok;
  struct n *next;
}node;

typedef struct s{
  node* top;
}stack;

int isEmpty(stack* stack);
stack* createStack();
int peep(stack* stack);
int pop(stack* stack);
void push(stack* stack,int op);
int isOperand(char ch);
int precedence(char op1,char op2);
int isOperator(char ch);
void printStack(stack* stack);
  
int main()
{
  FILE *fi,*fo;
  char ch;
  int num;
  fi=fopen("18CS10007_A2_P1_output.txt","r");
  fo=fopen("18CS10007_A2_P2_output.txt","w");
  stack *stack=createStack();
  while(1)
    {
      while((ch=fgetc(fi))!='\n' && ch!=EOF)
      {
        if(isOperand(ch))
        {
          ungetc(ch,fi);
          fscanf(fi,"%d",&num);
          push(stack,num);
        }
        else if(isOperator(ch))
        {
          switch(ch)
          {
            case '+' : push(stack,pop(stack) + pop(stack));
                       break;
            case '-' : push(stack,-(pop(stack)-pop(stack)));
                       break;
            case '*' : push(stack,pop(stack)*pop(stack));
                       break;
            case '/' : 
                      {
                        int x=pop(stack),y=pop(stack);
                        push(stack,y/x);
                        break;
                      }
            case '%' : 
                      {
                        int x=pop(stack),y=pop(stack);
                        push(stack,y%x);
                        break;
                      }
          }
        }
      }
      if(ch==EOF)
        break;
      fprintf(fo,"%d\n",pop(stack));
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

int peep(stack* stack)
{
  return stack->top->tok;
}

int pop(stack* stack)
{
  int c;
  node *p;
  p=stack->top;
  stack->top=stack->top->next;
  c=p->tok;
  free(p);
  return c;
}

void push(stack* stack,int op)
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