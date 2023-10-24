#include <iostream>
#include <string>
#include <map>
#include<cmath>
#include<algorithm>
#include <vector>


using namespace std;
bool isValid(char c)
{
    //problem with inverted input
    if (!(c >= 'a' && c <= 'z'))
        return false;
    return true;
}
bool checkSOP(string str) {
    // bool plus_sign = false;
    // bool last_plussign=false; //to check if there is pus sign at the end

    // for (int i=0;i<str.length();i++) {
    //     char c=str[i];
    //     if (c == '+') {
    //         if(i==0 || i==str.length()-1)
    //         {
    //             last_plussign=true;
    //             return false;
    //         }
    //         plus_sign = true;

    //     } else if (c == '(') {
    //         return false; // Contains '('
    //     } else if (!isValid(c)) {
    //         return false; // Invalid character
    //     }

    // }

    // return plus_sign && !last_plussign;

        //nours updated code (try it out ya gama3a garabo el cases kolaha) 
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



void display(vector<bool> k) {
    for (int i = 0; i < k.size(); i++) {
        cout << k[i] << ",";
    }
}

// Function to count how many literals do we have.
int count_variables(string s) {
    int num_of_variables;

    return 0;
}


//dec to binary in the proper order abc..  {status: done}
vector<bool> dec_to_bin(int num, int num_of_bits) {
    vector<bool>binary_values;
    int temp = 0;
    int i = 0;
    while (num > 0) {

        // storing remainder in binary array 
        binary_values.push_back(num % 2);
        num = num / 2;
        i++;
    }
    while (i < num_of_bits) {         //continuer the remaining places with zeros
        binary_values.push_back(0);
        i++;
    }
    // Inveting the order of the array so that it match the order of the literals.
    reverse(binary_values.begin(), binary_values.end());
    return binary_values;
}



vector<string> separator_SOP(string s) {
    vector<string> terms;
    string term = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '+') {
            terms.push_back(term);
            term = "";
        }
        else {
            term += s[i];
        }
    }
    terms.push_back(term);


    return terms;
}

bool calculate_expression_SOP(vector<bool> values, string term, map<char, int>indx) {    //bcd
    bool anding = 1;
    for (int i = 0; i < term.size(); i++) {
        if (i + 1 < term.size() && term[i + 1] == '\'') {
            anding = (anding && !(values[indx[term[i]]]));
            i++;
        }
        else {
            anding = (anding && values[indx[term[i]]]);
        }
    }
    return anding;
}

bool calculate_function_SOP(vector<bool> values, string s, map<char, int>indx)
{
    bool res = 0;

    vector<string> terms;

    if (checkPOS(s)) { //ab+bc

    }
    else { //SoP
        terms = separator_SOP(s);
        for (int i = 0; i < terms.size(); i++) {
            res = (res || calculate_expression_SOP(values, terms[i], indx));
        }
        return res;

    }


}


vector<char> NumberOfLiterals(string str) {
    vector<char> literals; // Use char instead of string to store individual characters

    for (char c : str) {
        if (isValid(c)) {
            literals.push_back(c);
        }
    }

    // Sort and remove duplicates
    sort(literals.begin(), literals.end());
    literals.erase(unique(literals.begin(), literals.end()), literals.end());

    int count = literals.size();
    return literals;
}

void truth_table_generator(string s) {

    map<char, int>indx;
    map<int, vector<bool>>minterms;
    map<int, vector<bool>>maxterms;
    string can_SOP = "";
    string can_POS = "";
    vector<char> literals = NumberOfLiterals(s);
    vector<bool> values;  // vector to contain all the temporary values that I will give to the literals
    //creating the indexing map
    for (int i = 0; i < literals.size(); i++) {
        indx[literals[i]] = i;
        cout << literals[i] << " | ";
    }
    cout << "f" << endl;
    for (int x = 0; x < literals.size(); x++) { cout << "-----"; }
    cout << endl;

    for (int i = 0; i < pow(2, literals.size()); i++) {   //i<(2*num_of_varialbes)
        values = dec_to_bin(i, literals.size());

        //##### displaying the truth table ######
        for (int j = 0; j < values.size(); j++) {
            cout << values[j] << " | ";
        }
        cout << calculate_function_SOP(values, s, indx) << endl;


        //##### Selecting minterms and maxterms ######
        if (calculate_function_SOP(values, s, indx))
            minterms[i] = values;
        else
            maxterms[i] = values;
    }

    cout << "\n\nMin\n";
    for (auto i = minterms.begin(); i != minterms.end(); i++) {
        cout << i->first << " - ";
        for (int j = 0; j < i->second.size(); j++)
            cout << i->second[j];
        cout << endl;
    }


    //##### Canonical SOP ######
    cout << "\Canonical SOP:  ";
    for (auto i = minterms.begin(); i != minterms.end(); i++) {
        for (int j = 0; j < i->second.size(); j++)
            if (i->second[j]) {
                can_SOP += literals[j];
            }
            else {
                can_SOP += literals[j];
                can_SOP += '\'';
            }

        can_SOP += '+';
    }
    can_SOP.pop_back();
    cout << can_SOP << endl;




    cout << "Max\n";
    for (auto i = maxterms.begin(); i != maxterms.end(); i++) {
        cout << i->first << " - ";
        for (int j = 0; j < i->second.size(); j++)
            cout << i->second[j];
        cout << endl;
    }

    //##### Canonical POS ######
    cout << "\Canonical POS:  ";
    for (auto i = maxterms.begin(); i != maxterms.end(); i++) {
        can_POS += '(';
        for (int j = 0; j < i->second.size(); j++)
        {
            if (i->second[j]) {
                can_POS += literals[j];
                can_POS += '\'';
            }
            else {
                can_POS += literals[j];
            }
            can_POS += '+';
        }
        can_POS.pop_back();
        can_POS += ')';
    }

    cout << can_POS << endl;

}



int countOnes(string binaryLiteral) //first step of the implicaton table: to see how many 1's are in each literal 
{
    int counter = 0;
    for (char c : binaryLiteral)
    {
        if (c == 1)
            counter++;

        return counter;
    }
}

int max(int a, int b)
{
    if (a>b)
    return a;
    else
    return b;
}
vector<vector<string>>find_groups(map<int,string>bin_dec)
{
   
    int size=0;
    map<int, std::string>::iterator it;
    //to define the size of vector<vector>
    for(it=bin_dec.begin();it!=bin_dec.end();it++)
    {
        int num=countOnes(it->second);
         size=max(size,num);
        
        
    }
     vector<vector<string>>v(size+1);
    
    for(it=bin_dec.begin();it!=bin_dec.end();it++)
    {
        int decimal=it->first;
        string value=it->second;
       int num= countOnes(value);
       v[num].push_back(value);
    }
    return v;
}


//third: we need to check for grey code - adjacent literals - start comparing 
//four: we need to replace the different bits with -
//five: if they are equal, ignore
//six: see if which PI's we did not use and print them 


int main()
{
    string expression;
    expression = "ac'+ab";
    ////cout << check(expression);

    truth_table_generator(expression);



    return 0;
}


