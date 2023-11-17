
#include <iostream>
#include <stack>
#include <cctype>
#include <math.h>
using namespace std;

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
            int num = 0;
            while (i < expression.size() && (isdigit(expression[i+1]))){
                num = num * 10 + (expression[i+1] - '0');
                i++;
            }
            numbers.push(-1 * num);
        } else if (isdigit(expression[i])) {
            int num = 0;
            while (i < expression.size() && (isdigit(expression[i]))){
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            numbers.push(num);
        } else if (expression[i] == '(') {
            operators.push(expression[i]);
        } else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '('){
                double second = numbers.top();
                numbers.pop();
                double first = numbers.top();
                numbers.pop();
                char op = operators.top();
                operators.pop();
                numbers.push(eval(first, second, op);
            } 
            operators.pop();
        } else if (isoperator(expression[i])) {
            while (!operators.empty() && pemdas(expression[i]) <= pemdas(operators.top())){
                double second = numbers.top();
                numbers.pop();
                double first = numbers.top();
                numbers.pop();
                char op = operators.top();
                operators.pop();
                numbers.push(eval(first, second, op);
            }
            operators.push(expression[i]);
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
        numbers.push(eval(first, second, op);
    }
    //returns the final value
    return numbers.top();
}
/*
int main() {
    string expression;
    cout << "Input the expression: ";
    getline(cin, expression);
    parser(expression);
    return 0;
}
*/

