//
//  main.cpp
//  Digital-project
//
//  Created by Amal Fouda on 21/10/2023.
//

#include <iostream>
#include <string>


using namespace std;
bool isValid(char c)
{
    //problem with inverted input
    if(!(c >= 'a' && c <= 'z') )
        return false;
    return true;
}
bool check_Sop(string str) {
    bool plus_sign = false;
    bool last_plussign=false; //to check if there is pus sign at the end

    for (int i=0;i<str.length();i++) {
        char c=str[i];
        if (c == '+') {
            if(i==0 || i==str.length()-1)
            {
                last_plussign=true;
                return false;
            }
            plus_sign = true;
            
        } else if (c == '(') {
            return false; // Contains '('
        } else if (!isValid(c)) {
            return false; // Invalid character
        }
        
    }

    return plus_sign && !last_plussign;
}
bool checkPOS(const string& expression)
{
    //if (expression.find('+') == string::npos || expression.find('(') != string::npos) //checks if there's no '+' or if there's an opening parenthesis
    //    return expression.find(')') != string::npos;


    int pos = 0;
    int len = expression.length();

    while (pos < len) {
        if (expression[pos] != '(' || !isalpha(expression[pos + 1]))//has to start with a parenthesis followed by a letter
            return false;

        pos += 2; // increment to see the character after the ( and the first literal

        while (pos < len && expression[pos] == '+' && isalpha(expression[pos + 1])) //keep reading while we have "+letter" pattern
            pos += 2; // move past the '+' and the letter
        
        if (pos >= len || expression[pos] != ')')//has to end in ) after we finish the first ()
            return false;

        pos++; // move past the ')' and check the next ()
    }

    return true;
}
string check(const string& expression)
{
    if (check_Sop(expression))
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
