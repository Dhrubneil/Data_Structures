#include<iostream>
#include<string.h>
#include<stack>

using namespace std;


void MisMatchMsg(char bracket);

string InfixToPostfix(string expression);

bool IsOpening(char c);

bool IsClosing(char c);

bool IsPair(char br1, char br2);

bool IsOperand(char c);

bool IsOperator(char c);

bool HasHigherPrecedence(char operand1, char operand2);



int main()
{
	string expression = "( { 2 * 3 } + [ 5 * 4 ] ) - 9";
	//cout<<"\nEnter an Infix Expression \n";
	//getline(cin,expression);
	cout<<"\nEntered Infix Expression : "<<expression<<"\n";
	string postfix = InfixToPostfix(expression);
	cout<<"\nEquivalent Postfix Expression = "<<postfix<<"\n";
}


string InfixToPostfix(string expression){
    stack<char> S;

    string postfix = "";
    char cont;

    for(int i = 0; i < expression.length(); i++){

        if(expression[i] == ' ' || expression[i] == ',') continue;

        else if(IsOperand(expression[i])){
            postfix += expression[i];
        }

        else if(IsOpening(expression[i])){
            S.push(expression[i]);
        }

        else if(IsClosing(expression[i])){
            while(!S.empty() && !IsOpening(S.top())){
                postfix += S.top();
                S.pop();
            }
            //S.pop();
	    if(S.empty()){
                MisMatchMsg(expression[i]);

                cout<<endl;
                //char cont;
                cout<<"Do You Want to Continue Ignoring Brackets Balance? [Y/N] : ";
                cin>>cont;

                if(cont == 'N'){
                    cout<<endl<<"Wrong Expression!!!"<<endl<<"Brackets are not Balanced."<<endl;
                    return "Cannot Evaluate Postfix";
                }
            }
	    	
            else if(IsPair(S.top(), expression[i])){
                S.pop();
            }
            else{
                MisMatchMsg(S.top());
                cout<<endl;
                //char cont;
                cout<<"Do You Want to Continue Ignoring Brackets Balance? [Y/N] : ";
                cin>>cont;

                if(cont == 'N'){
                    cout<<endl<<"Wrong Expression!!!"<<endl<<"Brackets are not Balanced."<<endl;
                    return "Cannot Evaluate Postfix";
                }
                else S.pop();
            }
        }

        else if(IsOperator(expression[i])){
            while(!S.empty() && !IsOpening(S.top()) && HasHigherPrecedence(S.top(), expression[i])){
                postfix += S.top();
                S.pop();
            }
            S.push(expression[i]);
        }
    }

    while(!S.empty()){
        postfix += S.top();
        S.pop();
    }

    return postfix;
}

bool IsOpening(char c){

    if(c == '(' || c == '{' || c == '[')return true;

    return false;
}

bool IsClosing(char c){

    if(c == ')' || c == '}' || c == ']')return true;

    return false;
}

bool IsPair(char br1, char br2){

    if(br1 == '(' && br2 == ')')return true;
    else if(br1 == '{' && br2 == '}')return true;
    else if(br1 == '[' && br2 == ']')return true;

    return false;
}

void MisMatchMsg(char bracket){
    if(bracket == '('){
        cout<<endl<<"\t\tMismatch of Copulation!!!"<<endl;
        cout<<"\n\t\tA \'"<<bracket<<"\' Must be Followed by \'"<<(char)(bracket+1)<<"\'"<<endl;
    }

    else if(bracket == '{' || bracket == '['){
        cout<<endl<<"\t\tMismatch of Copulation!!!"<<endl;
        cout<<"\n\t\tA \'"<<bracket<<"\' Must be Followed by \'"<<(char)(bracket+2)<<"\'"<<endl;
    }
	
    else if(bracket == ')'){
        cout<<endl<<"\t\tMismatch of Copulation!!!"<<endl;
        cout<<"\t\tA \'"<<bracket<<"\' Must Have a Following \'"<<(char)(bracket-1)<<"\'"<<endl;
    }

    else if(bracket == '}' || bracket == ']'){
        cout<<endl<<"\t\tMismatch of Copulation!!!"<<endl;
        cout<<"\t\tA \'"<<bracket<<"\' Must Have a Following \'"<<(char)(bracket-2)<<"\'"<<endl;
    }
}

bool IsOperand(char c){

    if(c >= 'a' && c <= 'z')return true;
    else if(c >= 'A' && c <= 'Z')return true;
    else if(c >= '0' && c <= '9')return true;

    return false;
}

bool IsOperator(char c){

    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return true;

    return false;
}

bool IsRightAssociative(char Operator){

    if(Operator == '^')return true;
    return false;
}

int GetOperatorWeight(char c){

    int weight = -1;

    switch(c){
        case '+':
        case '-':
            weight = 1;
            break;

        case '*':
        case '/':
            weight = 2;
            break;

        case '^':
            weight = 3;
            break;
    }
    return weight;
}

bool HasHigherPrecedence(char operator1, char operator2){

    int op1Weight = GetOperatorWeight(operator1);
    int op2Weight = GetOperatorWeight(operator2);

    if(op1Weight == op2Weight){

        if(IsRightAssociative(operator1)) return false;

        return true;
    }

    return op1Weight > op2Weight ? true:false;
}
