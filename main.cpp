#include <iostream>
#include <string>

using namespace std;

bool correctOrder(const string& expression)
{

}

bool checkSOP(const string& expression) 
{
    if (expression.find('+') != string::npos) //checks if there is a +
        if (expression.find('(') == string::npos)//and no opening parenthesis
            return true;
    return false; 
}

bool checkPOS(const string& expression) 
{
    if (expression.find('+') == string::npos || expression.find('(') != string::npos) //checks if there's no '+' or if there's an opening parenthesis
        return expression.find(')') != string::npos;
    
    return false; 
}

string check(const string& expression) 
{
    if (checkSOP(expression)) 
        return "SOP";
    else if (checkPOS(expression)) 
        return "POS";
    else 
        return "Neither SOP nor POS";
}

int main() 
{
    string expression;
    cout << "Enter the boolean function: " << '\n';
    cin >> expression; 
    cout << check(expression); 

    return 0;
}
