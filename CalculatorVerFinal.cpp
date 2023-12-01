
#include <iostream> //include io
#include <stack> //using the stack module
#include <cctype> //using module for isdigit and isspace
#include <math.h> //math module
using namespace std; //using standard namespace

double eval(double x, double y, char oper) { //eval func - takes two numbers and a char as an operator
    switch(oper) { //switch case based on the operator
        case 37: //% sign operator
            {
            int temp = x; //temp val to check valid x input
            double temp2 = x - temp; //second temp val - subtratcts temp from x to see if the int conversion caused problems
            if (temp2 != 0) { //if not zero
                throw "Modulo inputs must be integers"; //throw modulo error
            }
            temp = y; //temp val to check valid y input
            temp2 = y - temp; //second temp val - subtracts temp from y to see if the int conversion caused problems
            if (temp2 != 0){ //if not zero
                throw "Modulo inputs must be integers"; //throw modulo error
            }
            int x2 = x; //new assignment
            int y2 = y; //new assignmnet
            return x2 % y2; //return modulated val
            }
        case 42: //* operator
            return x * y; //return x * y
        case 43: //+ operator
            return x + y; //return x + y
        case 45: //- operator
            return x - y; //return x - y
        case 47: //'/' operator
            if (y == 0){ //if y = 0
                throw "Division by zero"; //throw divide by zero error
            }
            return x / y; //return x/y
        case 94: //^ operator
            return pow(x,y); //return x^y
        default: //If the given operator is not recognized.
            throw "Invalid operator"; //throw error
    }
}

//Function for defining operators precedence according to pemdas
int pemdas(char op){ //takes an op as param
    if (op == '^') return 3; //if ^, max prescidence so return 3
    if (op == '*' || op == '/' || op == '%') return 2; //if */%, tier two prescidence, so return 2
    if (op == '+' || op == '-') return 1; //if +- return 1, tier 3 prescidene
    return 0; //return zero if none
}
//Function for determining if a character is an operator
bool isoperator(char op) { //takes the op as param
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '%'); //return true or false based on if it's an operator
}

//The parser function which handles most of the work of the program
double parser(const string& expression){ //takes the expression as param
    //creates two stacks for keeping track of numbers and operators
    stack<double> numbers; //num stack
    stack<char> operators; //op stack

    //iterates through the input string
    for (int i = 0; i < expression.size(); i++){ //iterates 0-(size-1)
        if (isspace(expression[i])){ //continue if space (dead character)
            continue;
        } else if (expression[i] == '-' && expression[i+1] == '('){ //check for expression negation
            numbers.push(-1); //push -1 to num stack
            operators.push('*'); //push multiplication to op stack
        } else if (expression[i] == '+' && expression[i+1] == '('){ //check for positive expression
            continue; //continue (does actually effect the outcome)
        } else if (expression[i] == '+' && (expression[i+1] == 'p' || expression[i+1] == 'e' || isdigit(expression[i+1]))){ //if the expression detects p (pi) or e and + before it, continue (avoids error)
            continue; //continue
        } else if (expression[i] == '-' && expression[i+1] == 'e'){ //if -e is detected, push -2.7... to the num stack
            const double e = -2.71828182845904523536; //sets e val
            i++; //increments i because its checking two chars
            numbers.push(e); //pushes e to the num stack
        } else if (expression[i] == '-' && expression[i+1] == 'p' && expression[i+2] == 'i'){ //check for -pi
            const double pi = -3.14159265358979323; //set pi to -3.14...
            i++; i++; //increment i twice since we're looking at two chars
            numbers.push(pi); //push pi to nums
        } else if (expression[i] == 'e'){ //if regular e is detected
            const double e = 2.71828182845904523536; //set e to 2.7...
            numbers.push(e); //push e to nums
        } else if (expression[i] == 'p' && expression[i+1] == 'i'){ //if regular pi is detected
            const double pi = 3.14159265358979323; //set pi to 3.14...
            i++; //increment i because we're looking at two chars
            numbers.push(pi); //push pi to nums
        } else if (expression[i] == '-' && isdigit(expression[i+1])){ //if a negative number is detected
            if (!isspace(expression[i-1]) && i != 0 && expression[i-1] != '('){ //makes sure that there isnt any miss input like 1-1
                throw "Operators must be surrounded by spaces"; //if there is, throw error
            }
            if (expression[i-1] != '(' && !isoperator(expression[i-2]) && i != 0){ //verifies that there arent input errors like 1 -1
                throw "Operands without operator"; //throw error
            }
            int num = 0; //num = zero
            while (i < expression.size() && (isdigit(expression[i+1]))){ //iterates as long as there is a digit - used to account for multi digit nums
                num = num * 10 + (expression[i+1] - '0'); //continuously "appends" the new digit to the old
                i++; //increments i
            }
            numbers.push(-1 * num); //passes the negative value to nums
        } else if (isdigit(expression[i])) { //if not negative digit
            int num = 0; //num = 0
            int startIndex = i; //sets start index to current
            while (i < expression.size() && (isdigit(expression[i]))){ //iterates as long as there is a digit - used to account for multi digit nums
                num = num * 10 + (expression[i] - '0'); //continuously "appends" the new digit to the old
                i++; //increments i
            }
            i--; //decrements i
            if (numbers.empty()) numbers.push(num); //if nums is empty, push the num
            else if (!(isoperator(expression[startIndex-1]) || expression[startIndex - 1] == '(' || ((isoperator(expression[startIndex - 2]) || expression[startIndex - 2] == '(') && isspace(expression[startIndex-1]))) && !(isoperator(expression[i+1]) || expression[i+1] == ')' || ((isoperator(expression[i+2]) || expression[i+2] == ')') && isspace(expression[i+1]))) && ((i+1) != expression.size())){ //this line sucks, but essentially all it's doing is ensuring that operators have nums or expression associated with them - in the updated code version, this is somewhat redundant, though may catch an edge case
                throw "Operands without operator"; //throw error
            }
            numbers.push(num); //push num to numbers
        } else if (expression[i] == '(') { //if opening parenthesis are detected
            if (expression[i+1] == ')'){ //if closing parenthesis immediately follow
                throw "Empty parenthesis"; //throw empty parenthesis error
            } 
            operators.push(expression[i]); //push the expression to ops
        } else if (expression[i] == ')') { //if closing parenthesis detected
            if (expression[i+1] == '('){ //if immediately followed by open
                throw "Implicit multiplication is not defined"; //throw error - no implicit multiplication i.e. (5)(6)
            }
            while (!operators.empty() && operators.top() != '('){ //while ops isnt empty and the top isnt '(''
                double second = numbers.top(); //second = top num
                numbers.pop(); //pop num
                double first = numbers.top(); //first = top num
                numbers.pop(); //pop num
                char op = operators.top(); //op = top op
                operators.pop(); //pop op
                numbers.push(eval(first, second, op)); //push the evaluated num to nums
            } 
            operators.pop(); //pop ops
        } else if (isoperator(expression[i])) { //if an op is detected
            if(!((isspace(expression[i-1]) && (isspace(expression[i+1]))))){ //if it's not surrounded by spaces
                throw "Operators must be surrounded by spaces"; //throw error
            }
            if(!(( (isdigit(expression[i-2]) || (expression[i-2] == 'i' && expression[i-3] == 'p') || expression[i-2] == 'e') || expression[i-2] == ')') || ( ( isdigit(expression[i+2]) || (expression[i+2] == 'p' && expression[i+3] == 'i') || expression[i+2] == 'e' ) || expression[i+2] == '('))){ //this essentially verifies that ops have operands - semi redundant but may still catch edge cases
               throw "Operator without operands"; //throw error
            }
            while (!operators.empty() && pemdas(expression[i]) <= pemdas(operators.top())){ //while ops isnt empty pedmdas of i <= pemdas of top op
                double second = numbers.top(); //second = top num
                numbers.pop(); //pop top num
                double first = numbers.top(); //first = top num
                numbers.pop(); //pop top num
                char op = operators.top(); //op = top op
                operators.pop(); //pop top op
                numbers.push(eval(first, second, op)); //push the newly evaluated number to nums
            }
            operators.push(expression[i]); //push expression to ops
        }
        else{ //else
            throw "Invalid character"; //throw invalid character
        }
        
    } 
    //when done iterating it goes through the stacks and gets the final value
    while (!operators.empty()){ //while ops isnt empty
        double second = numbers.top(); //second = top num
        numbers.pop(); //pop top num
        double first = numbers.top(); //firt = top num
        numbers.pop(); //pop top num
        char op = operators.top(); //op = top op
        operators.pop(); //pop top op
        numbers.push(eval(first, second, op)); //push newly evaluated num
    }
    //returns the final value
    return numbers.top(); //return top, aka the last val
}


int main(){ //main
    string inputString; //declare string for input
    cout << "Input the expression: "; //prompt user
    getline(cin, inputString); //cin their input
    try { //try for try except block
        int closed = 0; //closes counter
        for (int i = 0; i < inputString.length(); i++){ //iterate over the input
            if (inputString[i] == '('){ //if open is detected
                closed++; //increment closed
            }else if(inputString[i] == ')'){ //else if close is detected
                closed--; //decrement closed
                if (closed < 0){ //if closed is less than zero
                    throw "Invalid Grouping Symbols"; //throw invalid grouping symbols
                }
            }
        }
        if(closed != 0){ //if closed isnt zero
            throw "Invalid Grouping Symbols"; //throw invalid grouping symbols
        }
        
        double operands, operators = 0; //set operands and operators to zero
        for (int i = 0; i < inputString.size(); i++){; //iterate over input string
            if (isspace(inputString[i])){ //if space
                continue; //continue
            } else if (inputString[i] == '('){ //if parenthesis, continue
                continue; //continue
            } else if (inputString[i] == ')'){ //if parenthesis, continue
                continue; //continue
            } else if ((inputString[i] == '-' || inputString[i] == '+') && inputString[i+1] == '('){ //if +( or -(
                continue; //continue
            } else if (inputString[i] == '+' && inputString[i+1] == 'p' || inputString[i+1] == 'e' || isdigit(inputString[i+1])){ //if +pi +e or +digit
                continue; //continue
            } else if (inputString[i] == 'e'){ //if e
                operands++; //increment operands
            } else if (isdigit(inputString[i])){ //if its a digit
                while (i < inputString.size() && isdigit(inputString[i])){ //increment while not past length and still i is still a digit
                    i++; //increment i
                }
                operands++; //increment operands
            } else if (inputString[i] == 'p' || inputString[i] == 'e'){ //if p or e 
                if (inputString[i] == 'e') i++; //if e increment i once
                else i++; i++; //else increment it twice
                operands++; //increment operands
            } else if (inputString[i] == '-' && (inputString[i+1] == 'p' || inputString[i+1] == 'e')) { //if -pi or -e
                i++; //increment i
                if (inputString[i] == 'e') i++; //if e, incrment once
                else i++; i++; //else increment twice
                operands++; //increment ops
            } else if ((inputString[i]) == '-' && isdigit(inputString[i+1])){ //if negative digit
                i++; //increment i
                while (i < inputString.size() && isdigit(inputString[i])){ //while less than length and i is digit
                    i++; //increment i
                }
                operands++; //increment operands
            } else if (isoperator(inputString[i])){ //if its an operator
                operators++; //increment operators
            } 
        }

        operands--; //decrement operands
        if (operands != operators){ //if theyre not equal
            throw "Invalid combinations of operators and operands, or invalid spacing."; //throw error
        }
        
        double returnThis = parser(inputString); //return val is pareser called on the input
        cout << returnThis << endl; //cout the input
    }
    catch(const char* errorMsg){ //catch any throw errors
        string errorString = errorMsg; //error string = error message
        cout << "An error occured during evaluation: " + errorString << endl; //cout the error with its message
    }
    
}




