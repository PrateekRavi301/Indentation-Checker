#include<stdio.h>
#include<stdlib.h>
#define stack_size 1000

struct stack
{
	int arr[stack_size];
	int top;
};

typedef struct stack Stack;

//push function
void Push(Stack* s,int a)
{
	s->top++;
	s->arr[s->top]=a;
}

//pop function
void Pop(Stack* s)
{
	s->top--;
}

int isEmpty(Stack* s)
{
	if(s->top==-1) return 1;
	else return 0;
}
int check(Stack* s,int count,int line_count)
{
	if(isEmpty(s))
	{
		Push(s,count);
		return 0;
	}
	else
	{
		if(s->arr[s->top]==count)
		{return 0;}
		else if(s->arr[s->top] < count)
		{
			Push(s,count);
			return 0;
		}
		else
		{
			Pop(s);
			if(s->arr[s->top]!=count)
			{
				printf("No Proper indentation in line %d\n",line_count);
				return 1;
			}
			else return 0;
		}
	}
}

int main(int argc, char const *argv[])
{
	FILE* fptr;
	Stack s;
	s.top=-1;
	char ch;
	int i=1;
	int space_counter=0;
	int line_count=1;
	int count=0;
	fptr=fopen(argv[1],"r");
	if(fptr==NULL)
	{
		printf("Cannot open File\n");
		return 0;
	}

	while(ch!=EOF)
	{
		ch=fgetc(fptr);
		if(ch==' ' && count==0) space_counter++;
		else if(ch=='\t' && count==0) space_counter+=4;
		else
		{
			count++;
		}
		if(count!=0)
		{
			if(check(&s,space_counter,line_count)) return 0;
		}
		if(ch=='\n')
		{
			line_count++;
			count=0;
			space_counter=0;
		}
	}
	printf("Proper indentation\n");
	return 0;
}
