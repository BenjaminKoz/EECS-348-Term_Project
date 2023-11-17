/*
Implementation of the evaluator function for the Arithmetic Expression Calculator software

*/
#include <math.h>
#include <iostream>


//Function to evaluate 2 numbers with a given operator.
double eval(int x, int y, char oper) {
    switch(oper) {
        case 37: //% sign operator
            return x % y;
        case 42: //* operator
            return x * y;        
        case 43: //+ operator
            return x + y;
        case 45: //- operator
            return x - y;
        case 47: //'/' operator
            if(y == 0) throw "Divide by zero error";
            return x / y;
        case 94: //^ operator
            return pow(x,y);
        default: //If the given operator is not recognized.
            throw "Invalid operator";
    }
}

/* Main function used for testing functionality
int main() {
    double ans = eval(2,2,'%');
    std::cout << ans;
}
*/