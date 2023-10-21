//
//  main.cpp
//  Digital-project
//
//  Created by Amal Fouda on 21/10/2023.
//

#include <iostream>
#include <string>

using namespace std;
bool isValidinput(char c)
{
    return c>='a' && c<='z';
}

bool checkSOP(const string& expression)
{
    for (char c : expression) {
            if (c == '+') {
                if (expression.find('(') == std::string::npos) {
                    return true; // Found '+' without '('
                }
            }
            else if (!isValidinput(c)) {
                return false; // Invalid character
            }
        }
        return false;
}

bool checkPOS(const string& expression)
{
    if (expression.find('+') == std::string::npos || expression.find('(') != std::string::npos) {
            for (char c : expression) {
                if (c == ')') {
                    return true; // Found ')' without '+'
                }
                else if (!isValidinput(c)) {
                    return false; // Invalid character
                }
            }
        }
        return false;
}

string check(const string& expression)
{
    if (checkSOP(expression))
        return "SOP";
    else if (checkPOS(expression))
        return "POS";
    else
        return "enter valid input";
}

int main()
{
    string expression;
    cout << "Enter the boolean function: " << '\n';
    cin >> expression;
    cout << check(expression);

    return 0;
}
