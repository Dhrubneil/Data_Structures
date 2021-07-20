#include<iostream>
#include<string.h>
#include<stack>
#include<math.h>

using namespace std;

int EvaluatePostfix(string expression);

int PerformOperation(char Operator, int operand1, int operand2);

bool isOperator(char c);

bool isNumericDigit(char c);


int main(){

    string expression = "2 3 ^ 5 4 * + 9 -";
    //cout<<endl<<"Enter a Valid Postfix Expression : "<<endl;
    //getline(cin, expression);

    int result = EvaluatePostfix(expression);
    cout<<endl<<"The value of the postfix expression ( "<<expression<<" ) is: "<<result<<endl;

    string fn = "Niloy";
    string mn = "Kumer";
    string ln = "Bhadra";

    cout<<endl<<fn + " " + mn + " " + ln<<endl;
}

int EvaluatePostfix(string expression){
    stack<int> S;

    for(int i = 0; i < expression.length(); i++){

        if(expression[i] == ' ' || expression[i] == ',')continue;

        else if(isOperator(expression[i])){
            int operand2 = S.top();
            S.pop();

            int operand1 = S.top();
            S.pop();

            int result = PerformOperation(expression[i], operand1, operand2);
            S.push(result);
        }

        else if(isNumericDigit(expression[i])){

            int operand = 0;

            while(i < expression.length() && isNumericDigit(expression[i])){

                operand = operand*10 + (expression[i] - '0');
                i++;
            }
            i--;

            S.push(operand);
        }
    }
    return S.top();
}

int PerformOperation(char Operator, int operand1, int operand2){

    if(Operator == '+') return operand1 + operand2;
    else if(Operator == '-') return operand1 - operand2;
    else if(Operator == '*') return operand1 * operand2;
    else if(Operator == '/') return operand1 / operand2;
    else if(Operator == '^') return pow(operand1, operand2);

    else cout<<endl<<"Unexpected Error"<<endl;
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
