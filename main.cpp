#include <iostream>
#include <string>

using namespace std;
bool isValidinput(char c) //checks that the input is only the alphabet 
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
