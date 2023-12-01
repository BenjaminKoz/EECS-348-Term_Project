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
        double returnThis = parser(inputString);
        cout << returnThis;
    }
    catch(const char* errorMsg){
        string errorString = errorMsg;
        cout << "An error occured during evaluation: " + errorString;
    }
    
}
