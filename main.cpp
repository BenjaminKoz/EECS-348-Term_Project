//Code Authors: Benjamin Kozlowski, MJ McGee, Jacob Leehy, Steve Gan, Nicholas Hausler
//Project: Arithmetic Expression Evaluator in C++

#include <iostream>
#include <iomanip>
using namespace std;

double solveit(char expression[100]);

int main(){
    char expression[100] = {0};
    double solution;
    cout << "Please input your arithmetic expression: ";
    cin >> expression;
    solution = solveit(expression);
    cout << "The solution to your arithmetic expression is " << solution << endl;
}

double solveit(char expression[100]){
    return;
}