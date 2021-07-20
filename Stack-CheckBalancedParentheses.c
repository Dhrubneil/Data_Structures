#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

char *stack;
int top = -1;

void push(char c){
    top++;
    stack[top] = c;
}

void pop(){
    top--;
}

char topElement(){
    return stack[top];
}

bool isEmpty(){
    if(top == -1)return true;
    return false;
}

bool arePair(char a, char b){
    if(a == '(' && b == ')')return true;
    else if(a == '{' && b == '}')return true;
    else if(a == '[' && b == ']')return true;
    return false;
}

bool isBalanced(char expression[]){
    int length = strlen(expression);

    stack = (char*)malloc(length*sizeof(char));
    int i;
    for(i = 0; i < length; i++){
        char c = expression[i] ;
        if(c == '(' || c == '{' || c == '['){
            push(c);
           }
        else if(c == ')' || c == '}' || c == ']'){
            if(isEmpty() || !arePair(topElement(), c)){
                return false;
            }
            else{
                pop();
            }
        }
    }
    return isEmpty()?true:false;
}

int main(){
    char expression[] = "[(){{}}]";

    if(isBalanced(expression))
        printf("Balanced");
    else{
        printf("Not Balanced");
    }
}
