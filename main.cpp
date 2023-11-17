#include <iostream>
#include <string>
#include <cctype>
#include <math.h>
using namespace std;

int main(){
    string inputString;
    std::cout << "Input your expression to be evaluated: ";
    std::cin >> inputString;
    try {
        double returnThis = parser(inputString);
        cout << returnThis;
    }
    catch(const char* errorMsg){
        string errorString = errorMsg;
        cout << "An error occured during evaluation: " + errorString;
    }
    
}
