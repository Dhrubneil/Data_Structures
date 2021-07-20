#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


void EvaluatePostfix(char exp[]){
    int k = 0;
    int ni = -1;
    int *nop;
    nop = (int*)malloc(sizeof(int));

    printf("\nEvaluation of Postfix Expression : %s\n", exp);
    printf("---------------------------------------------------");
    for(k = 0; k < strlen(exp); k++){
        if(((int)exp[k] >= 48) && ((int)exp[k] <= 57)){
            ni++;
            nop = (int*)realloc(nop, (ni+1)*sizeof(int));
            nop[ni] = (int)exp[k]-48;
            printf("\n\nScanned =  %d\tIndex = %d\tInserted = %d", nop[ni], ni, nop[ni]);
        }
        else{
            if(exp[k] == '*'){
                ni--;
                nop[ni] = nop[ni] * nop[ni+1];
                printf("\n\nScanned = \'%c\'\tIndex = %d\tInserted = %d", exp[k], ni, nop[ni]);
            }
            else if(exp[k] == '/'){
                ni--;
                nop[ni] = nop[ni] / nop[ni+1];
                printf("\n\nScanned = \'%c\'\tIndex = %d\tInserted = %d", exp[k], ni, nop[ni]);
            }
            else if(exp[k] == '+'){
                ni--;
                nop[ni] = nop[ni] + nop[ni+1];
                printf("\n\nScanned = \'%c\'\tIndex = %d\tInserted = %d", exp[k], ni, nop[ni]);
            }
            else if(exp[k] == '-'){
                ni--;
                nop[ni] = nop[ni] - nop[ni+1];
                printf("\n\nScanned = \'%c\'\tIndex = %d\tInserted = %d", exp[k], ni, nop[ni]);
            }
            else if(exp[k] == '^'){
                ni--;
                nop[ni] = pow(nop[ni], nop[ni+1]);
                printf("\n\nScanned = \'%c\'\tIndex = %d\tInserted = %d", exp[k], ni, nop[ni]);
            }
        }
    }
    printf("\n\n---------------------------------------------------");
    printf("\n\nThe value of the postfix expression is: %d\n", nop[ni]);
    free(nop);
}


int main(){
    char exp[] = "23^54*+9-";

    int *op;
    int i;
    int index = -1;
    op = (int*)malloc(sizeof(int));

    printf("\nThe operands are put into a list :\n");
    printf("---------------------------------------------------");
    for(i = 0; i < strlen(exp); i++){
        int as = (int)exp[i];

        if(((as-48) >= 0) && ((as-48)<= 9)){
            index++;
            printf("\nIndex = %d\tOperand = %d", index, (int)exp[i]-48);            //op[index] = as - 48;
            op = (int*)realloc(op, (index+1)*sizeof(int));
            op[index] = as - 48;
        }
    }

    int j = 0;
    printf("\n\nOperands List : ");;
    for(j = 0; j <= index; j++){
        printf("%d ", op[j]);
    }
    printf("\n---------------------------------------------------\n");

    EvaluatePostfix(exp);

    //printf("\n\n%d\n", '2' - '0');

    free(op);
}
