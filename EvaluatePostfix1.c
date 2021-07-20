#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include<windows.h>//can be used to Sleep(int time_in_ms)
#define MAX 100

int *stack;
int top = -1;

//stack = (int*)malloc(sizeof(int));  // malloc() should be called in run-time, not in compile-time
                                      // malloc() should not be called before the program starts, i.e. except from main
                                      // explicitly or implicitly
                                      // calling malloc() at this point will generate the following error

                                      // warning: data definition has no type or storage class
                                      // warning: type defaults to 'int' in declaration of 'stack' [-Wimplicit-int]
                                      // error: conflicting types for stack

void push(int operand){
    top++;
    //stack = (int*)realloc(stack, sizeof(int));
    stack[top] = operand;
}

void pop(){
    top--;
}

int topElement(){
    return stack[top];
}


int PerformOperation(char Operator, int operand1, int operand2);

int EvaluatePostfix(char expression[]);

int EvaluatePrefix(char expression[]);

bool isOperator(char c);

bool isNumericDigit(char c);


int main(){

    //stack = (int*)malloc(MAX*sizeof(int));

    char expression[MAX];// = "2 3 * 5 4 * + 9 -";
    printf("\nEnter a Postfix Expression : ");
    gets(expression);

    int result = EvaluatePostfix(expression);
    printf("\n\nValue of the Postfix Expression ( %s ) : %d\n", expression, result);

    //free(stack);
    printf("\nstack[top] = %d\n", stack[top]);

    //stack = (int*)realloc(stack, sizeof(int));

    char expression1[MAX];// = "- + ^ 2 3 * 5 4 9";
    printf("\nEnter a Prefix Expression : ");
    gets(expression1);


    int result1 = EvaluatePrefix(expression1);
    printf("\n\nValue of the Prefix Expression ( %s ) : %d\n", expression1, result1);


    printf("\nstack[top] = %d\n", stack[top]);

}

int EvaluatePostfix(char expression[]){

    stack = (int*)malloc(MAX*sizeof(int));

    int i = 0;
    for(i = 0; i < strlen(expression); i++){

        if(expression[i] == ' ' || expression[i] == ',')continue;

        else if(isOperator(expression[i])){

            int operand2 = topElement();
            pop();

            int operand1 = topElement();
            pop();

            int result = PerformOperation(expression[i], operand1, operand2);
            push(result);
        }

        else if(isNumericDigit(expression[i])){

            int operand = 0;

            while(i < strlen(expression) && isNumericDigit(expression[i])){

                operand = operand * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            push(operand);
        }
    }
    int output = stack[top];
    free(stack);
    return output;
}

int PerformOperation(char Operator, int operand1, int operand2){

    if(Operator == '+')return operand1 + operand2;
    else if(Operator == '-')return operand1 - operand2;
    else if(Operator == '*')return operand1 * operand2;
    else if(Operator == '/')return operand1 / operand2;
    else if(Operator == '^')return pow(operand1, operand2);

    else
        printf("\nUnexpected Error!!!\n");

    return -1;
}

bool isOperator(char c){

    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return true;

    return false;
}

bool isNumericDigit(char c){

    if(c >= '0' && c <= '9')
        return true;

    return false;
}


int EvaluatePrefix(char expression[]){

    stack = (int*)malloc(MAX*sizeof(int));

    int i = 0;
    for(i = strlen(expression)-1; i >= 0 ; i--){

        if(expression[i] == ' ' || expression[i] == ',')continue;

        else if(isOperator(expression[i])){

            int operand1 = topElement();
            pop();

            int operand2 = topElement();
            pop();

            int result = PerformOperation(expression[i], operand1, operand2);
            push(result);
        }

        else if(isNumericDigit(expression[i])){

            int operand = 0;
            int pos = 0;

            while(i >= 0 && isNumericDigit(expression[i])){

                operand = operand + pow(10, pos)*(expression[i] - '0');
                pos++;
                i--;
            }
            i++;
            push(operand);
        }
    }
    int output = stack[top];
    free(stack);
    return output;
}

