#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
 * Item: An item that is being pushed to or popped from the stack
 *       It may be float (to be used while evaluating the postfix)
 *       It may be char* (to be used while converting infix to postfix)
 */
typedef union {
	float fData;
	char* cpData;
} Item;
/*
 *
 */
typedef struct {
	char items[100];
	int top;
} Stack;

typedef struct{
    float items[100];
    int top;
}Stack1;
/*
 *
 */
 void init1(Stack1 *s) {
	s->top=0;
}
/*
 *
 */
/*
 *
 */
/*
 *
 */
float pop1(Stack1 *s) {
	float value;
	s->top--;
	value=s->items[s->top];
	return value;
}
/*
 *
 */
void push1(Stack *s, float val) {
	s->items[s->top]=val;
	s->top++;
}



void init(Stack *s) {
	s->top=0;
}
/*
 *
 */
int isEmpty(Stack *s) {
	if(s->top==0)
        return 1;
	else
        return 0;
}
/*
 *
 */
char top(Stack *s) {
	return s->items[s->top-1];
}
/*
 *
 */
char pop(Stack *s) {
	char value;
	s->top--;
	value=s->items[s->top];
	return value;
}
/*
 *
 */
void push(Stack *s, char val) {
	s->items[s->top]=val;
	s->top++;
}
/*
 *
 */
void destroy(Stack *s) {
    free(s);
}
/*
 * infixToPostfix: converts an expression in infix notation to
 *					to a postfix notation (Reverse-Polish Notation)
 *					ASSUME ^*+-/ operators
 *					e.g., 2 + 3 --> 2 3 +
 *					e.g., ( -2.5 + 3.14 ) * 4 --> -2.5 3.14 + 4 *
 */

int priority(char c){
switch (c)
{
    case '*':
    case '/':
    return 1;
    case '+':
    case '-':
    return 0;
    case '(':
    return 2;
}
}

int isDigit(char c){
    if (c==0||c==1||c==2||c==3||c==4|c==5||c==6||c==7||c==8||c==9)
    return 1;
    else return 0;
}
void infixToPostfix(char* infix,char* pofix)
{
	int i,j=0;
	Stack s;
	init(&s);
	for (i=0;i<strlen(infix);i++)
    {
        if(isDigit(infix[i])){
            /*printf("%c",infix[i]);*/
            pofix[j++]=infix[i];
        }

            else if(infix[i]==')')
        {
            while(!isEmpty(&s)&&top(&s)!= '(')
            {
                /*printf("%c",pop(&s));*/
                pofix[j++]=pop(&s);
            }
            pop(&s);
        }

        else if (isEmpty(&s))
            push(&s,infix[i]);
        else {
            while(!isEmpty(&s)&&priority(top(&s))>=priority(infix[i])&&top(&s)!='(')
            {
                    /*printf("%c",pop(&s));*/
                    pofix[j++]=pop(&s);
            }

                    push(&s,infix[i]);
        }
    }
    while(!isEmpty(&s)){
        /*printf("%c",pop(&s));*/
        pofix[j++]=pop(&s);
    }

}

float calculate(char c,float f, float s){
    if(c=='+')
        return(f+s);
    if(c=='-')
        return(f-s);
    if(c=='*')
        return(f*s);
    if(c=='/')
        return(f/s);
}
/*
 * evaluatePostfix: Evaluates an expression in postfix notation
 *					 (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 */
float evaluatePostfix(char* postfix)
{
    Stack1 evaluation;
    float f=0,s=0,v=0;

    init1(&evaluation);
    int i;
    for (i=0;i<strlen(postfix);i++)
    {
        if(isDigit(postfix[i]))
            push1(&evaluation,postfix[i]);
        else
        {
            s=pop1(&evaluation);
            f=pop1(&evaluation);
            v=calculate(postfix[i],f,s);
            push1(&evaluation,v);
        }
    }
    v=pop1(&evaluation);
	return v;
}
/*
 *
 */
void replaceNewLineBySpace(char *s) {
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
 *
 */
void main(){
    char infixExpr[256];
	char postfixExpr[256];

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        infixToPostfix(infixExpr, postfixExpr);
        printf("%s",postfixExpr);
		float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);

		printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
	}
}
