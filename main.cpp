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
bool checkSOP(string str) {

    //amal's inital code 
    /*bool plus_sign = false;
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

    return plus_sign && !last_plussign;*/

        //nours updated code (try it out ya gama3a garabo el cases kolaha 
    bool plus_sign = false; // to check if theres a + 
    bool last_char_was_plus = false; // to check we have no two consecutive '+'
    bool last_char_was_complement = false; // Ensures no two consecutive inversions

    for (int i = 0; i < str.length(); i++)//iterating through the expression string
    {
        char c = str[i];

        if (c == '+') 
        {
            if (i == 0 || i == str.length() - 1 || last_char_was_plus) //if we are at the beginning or end and we have a +
                return false; // its invalid 
            
            plus_sign = true; //after checking we dont have + at the beginning or end we change this variable to true 
            last_char_was_plus = true; //and this variable 
            last_char_was_complement = false; // reset after encountering '+'
        }
        else if (c == '\'') //if we have the inversion '
        {
            if (last_char_was_complement || last_char_was_plus)//to check we dont have consecutive inversion after + between literals
                return false; // its invalid
           
            last_char_was_complement = true; 
            last_char_was_plus = false; // reset after encountering a valid character
        }
        else if (isValid(c)) {
            last_char_was_plus = false; // reset after encountering a valid character
            last_char_was_complement = false; // reset after encountering a valid character
        }
        else return false; //its invalid
        
    }
    return plus_sign;
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

        if (pos < len && expression[pos] == '\'') 
            pos++;

        while (pos < len && expression[pos] == '+' && isalpha(expression[pos + 1]))  // Keep reading while we have "+letter" 
        {
            pos += 2; // move past the '+' and the letter

            //check for inversion '
            if (pos < len && expression[pos] == '\'') 
                pos++;
            
        }
        if (pos >= len || expression[pos] != ')')//check for closing )
            return false;

        pos++; // move past the ')'
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






void separator(string s) {

}


// Function to count how many literals do we have.
int count_variables(string s) {
    int num_of_variables;

    return 0;
}

//function that recieves values for each literal and the expression 
// and translate the expression into logic and find its value based on the vlues passed for literals.   {status: Not built yet}
bool calculate_function(bool values[], string s) {


    return values[0] && values[1];
}

//dec to binary in the proper order abc..  {status: done}
bool* dec_to_bin(int num, int num_of_bits) {
    bool* binary_values = new bool[num_of_bits];
    bool* reversed_binary_values = new bool[num_of_bits];

    int temp = 0;
    int i = 0;
    while (num > 0) {

        // storing remainder in binary array 
        binary_values[i] = num % 2;
        num = num / 2;
        i++;
    }
    while (i < num_of_bits) {         //continuer the remaining places with zeros
        binary_values[i] = 0;
        i++;
    }

    // Inveting the order of the array so that it match the order of the literals.
    for (int x = 0, j = i - 1; j >= 0; x++, j--)
        reversed_binary_values[x] = binary_values[j];

    for (int y = 0; y < i; y++) {
        cout << reversed_binary_values[y];
    }
    //cout<<endl;

    return binary_values;
}

void truth_table_generator(string s) {

    map<char, int>indx;
    int num_of_variables = 2;// = count_variables(s)

    bool* values = new bool[num_of_variables];  // array to contain all the temporary values that I will give to the literals

    //creating the indexing map
    for (int i = 0; i < num_of_variables; i++) {
        indx[char(97 + i)] = i;
    }
    cout << "ab---f" << endl;
    for (int i = 0; i < 4; i++) {   //i<(2*num_of_varialbes)
        values = dec_to_bin(i, num_of_variables);
        cout << "---";
        cout << calculate_function(values, s) << endl;
    }

}

int main()
{
    string expression;
    //cout << "Enter the boolean function: " << '\n';
    //cin >> expression;
    expression = "ab";
    //cout << check(expression);


    truth_table_generator(expression);

    //bool* binary_values = dec_to_bin(3, 5);


    return 0;
}
