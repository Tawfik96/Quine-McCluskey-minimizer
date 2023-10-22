//
//  main.cpp
//  Digital-project
//
//  Created by Amal Fouda on 21/10/2023.
//

#include <iostream>
#include <string>
#include <map>

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

void separator(string s) {

}


// Function to count how many literals do we have.
int count_variables(string s) {
    int num_of_variables;

    return num_of_variables;
}

void truth_table_generator(string s) {
    
    map<char, int>indx;
    int num_of_variables = 2;// = count_variables(s)
    for (int i = 0; i < num_of_variables; i++) {
        indx[] = i;
    }
}

int main()
{
    string expression;
    cout << "Enter the boolean function: " << '\n';
    cin >> expression;
    expression = "ab";
    //cout << check(expression);
    cout << char(97);
    cout << expression;
    

    return 0;
}
