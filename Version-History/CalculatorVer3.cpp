
#include <iostream>
#include <stack>
#include <cctype>
#include <math.h>
using namespace std;

double eval(double x, double y, char oper) {
    switch(oper) {
        case 37: //% sign operator
            {
            int temp = x;
            double temp2 = x - temp;
            if (temp2 != 0) {
                throw "Modulo inputs must be integers";
            }
            temp = y;
            temp2 = y - temp;
            if (temp2 != 0){
                throw "Modulo inputs must be integers";
            }
            int x2 = x;
            int y2 = y;
            return x2 % y2;
            }
        case 42: //* operator
            return x * y;        
        case 43: //+ operator
            return x + y;
        case 45: //- operator
            return x - y;
        case 47: //'/' operator
            if (y == 0){
                throw "Division by zero";
            }
            return x / y;
        case 94: //^ operator
            return pow(x,y);
        default: //If the given operator is not recognized.
            throw "Invalid operator";
    }
}

//Function for defining operators precedence according to pemdas
int pemdas(char op){
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}
//Function for determining if a character is an operator
bool isoperator(char op) {
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '%');
}

//The parser function which handles most of the work of the program
double parser(const string& expression){
    //creates two stacks for keeping track of numbers and operators
    stack<double> numbers;
    stack<char> operators;

    //iterates through the input string
    for (int i = 0; i < expression.size(); i++){
        if (isspace(expression[i])){
            continue;
        } else if (expression[i] == '-' && expression[i+1] == 'e'){
            const double e = -2.71828182845904523536;
            i++;
            numbers.push(e);
        } else if (expression[i] == '-' && expression[i+1] == 'p' && expression[i+2] == 'i'){
            const double pi = -3.14159265358979323;
            i++; i++;
            numbers.push(pi);
        } else if (expression[i] == 'e'){
            const double e = 2.71828182845904523536;
            numbers.push(e);
        } else if (expression[i] == 'p' && expression[i+1] == 'i'){
            const double pi = 3.14159265358979323;
            i++;
            numbers.push(pi);
        } else if (expression[i] == '-' && isdigit(expression[i+1])){
            if (!isspace(expression[i-1]) && i != 0 && expression[i-1] != '('){
                throw "Operators must be surrounded by spaces";
            }
            if (expression[i-1] != '(' && !isoperator(expression[i-2]) && i != 0){
                throw "Operands without operator";
            }
            int num = 0;
            while (i < expression.size() && (isdigit(expression[i+1]))){
                num = num * 10 + (expression[i+1] - '0');
                i++;
            }
            numbers.push(-1 * num);
        } else if (isdigit(expression[i])) {
            int num = 0;
            int startIndex = i;
            while (i < expression.size() && (isdigit(expression[i]))){
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            if (!(isoperator(expression[startIndex-1]) || (isoperator(expression[startIndex - 2]) && isspace(expression[startIndex-1]))) && !(isoperator(expression[i+1]) || (isoperator(expression[i+2]) && isspace(expression[i+1]))) && ((i+1) != expression.size())){
                throw "Operands without operator";
            }
            numbers.push(num);
        } else if (expression[i] == '(') {
            if (expression[i+1] == ')'){
                throw "Empty parenthesis";
            } 
            operators.push(expression[i]);
        } else if (expression[i] == ')') {
            if (expression[i+1] == '('){
                throw "Implicit multiplication is not defined";
            }
            while (!operators.empty() && operators.top() != '('){
                double second = numbers.top();
                numbers.pop();
                double first = numbers.top();
                numbers.pop();
                char op = operators.top();
                operators.pop();
                numbers.push(eval(first, second, op));
            } 
            operators.pop();
        } else if (isoperator(expression[i])) {
            if(!((isspace(expression[i-1]) && (isspace(expression[i+1]))))){
                throw "Operators must be surrounded by spaces";
            }
            if(!((isdigit(expression[i-2]) || expression[i-2] == ')') || (isdigit(expression[i+2]) || expression[i+2] == '('))){
               throw "Operator without operands";
            }
            while (!operators.empty() && pemdas(expression[i]) <= pemdas(operators.top())){
                double second = numbers.top();
                numbers.pop();
                double first = numbers.top();
                numbers.pop();
                char op = operators.top();
                operators.pop();
                numbers.push(eval(first, second, op));
            }
            operators.push(expression[i]);
        }
        else{
            throw "Invalid character";
        }
        
    } 
    //when done iterating it goes through the stacks and gets the final value
    while (!operators.empty()){
        double second = numbers.top();
        numbers.pop();
        double first = numbers.top();
        numbers.pop();
        char op = operators.top();
        operators.pop();
        numbers.push(eval(first, second, op));
    }
    //returns the final value
    return numbers.top();
}


int main(){
    string inputString;
    cout << "Input the expression: ";
    getline(cin, inputString);
    try {
        int closed = 0;
        for (int i = 0; i < inputString.length(); i++){
            if (inputString[i] == '('){
                closed++;
            }else if(inputString[i] == ')'){
                closed--;
                if (closed < 0){
                    throw "Invalid Grouping Symbols";
                }
            }
        }
        if(closed != 0){
            throw "Invalid Grouping Symbols";
        }
        
        double operands, operators = 0;
        for (int i = 0; i < inputString.size(); i++){;
            if (isspace(inputString[i])){
                continue;
            } else if (inputString[i] == '('){
                continue;
            } else if (inputString[i] == ')'){
                continue;
            } else if (isdigit(inputString[i])){
                while (i < inputString.size() && isdigit(inputString[i])){
                    i++;
                }
                operands++;
            } else if ((inputString[i]) == '-' && isdigit(inputString[i+1])){
                i++;
                while (i < inputString.size() && isdigit(inputString[i])){
                    i++;
                }
                operands++;
            } else if (isoperator(inputString[i])){
                operators++;
            } 
        }

        operands--;
        if (operands != operators){
            throw "Invalid combinations of operators and operands.";
        }
        
        double returnThis = parser(inputString);
        cout << returnThis << endl;
    }
    catch(const char* errorMsg){
        string errorString = errorMsg;
        cout << "An error occured during evaluation: " + errorString << endl;
    }
    
}





