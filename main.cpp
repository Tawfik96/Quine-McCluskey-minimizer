#include <iostream>
#include <string>
#include <map>
#include<cmath>
#include<algorithm>
#include <vector>
#include<iomanip>
#include <fstream>
#include <cstdlib>

using namespace std;
class Implicant
{
public:
    vector<int> indicies;
    string binary;
    bool combine = false;
    bool is_essential = false;

    bool operator==(const Implicant& other) const {
        return this->binary == other.binary;
    }
};
bool isValid(char c)
{
    //problem with inverted input
    if (!(c >= 'a' && c <= 'z'))
        return false;
    return true;
}

bool checkSOP(string str) {

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
bool checkPOS(const string& expression) {
    int pos = 0;
    int len = expression.length();

    while (pos < len) {
        // Expect an opening parenthesis followed by a letter
        if (expression[pos] != '(' || !isalpha(expression[pos+1]))
            return false;

        pos += 2; // move past the '(' and the first letter

        // Check if the literal is barred (has a `'` after it)
        if (pos < len && expression[pos] == '\'') {
            pos++;
        }

        // Keep reading while we have "+letter" pattern
        while (pos < len && expression[pos] == '+' && isalpha(expression[pos+1])) {
            pos += 2; // move past the '+' and the letter
            
            // Again, check for ' 
            if (pos < len && expression[pos] == '\'') {
                pos++;
            }
        }

        // After reading literals, expect a closing parenthesis
        if (pos >= len || expression[pos] != ')')
            return false;

        pos++; // move past the ')'
    }
    
    return true;
}

bool check(const string& expression)
{
    if (checkSOP(expression))
    {
        cout << "SOP" << endl;
        return true;

    }
    else if (checkPOS(expression))
    {
        cout << "POS" << endl;
        return true;
    }
    else
    {
        cout << "invalid input" << endl;
        return false;
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

vector<string> separator_POS(string s) {   //(a+b')(c)
    vector<string> terms;
    string term = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] != '(' && s[i] != '+') {
            if (s[i] == ')') {
                terms.push_back(term);
                term = "";
            }
            else
                term += s[i];
        }
    }
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

bool calculate_expression_POS(vector<bool> values, string term, map<char, int>indx) {    //bc'd
    bool oring = 0;
    for (int i = 0; i < term.size(); i++) {
        if (i + 1 < term.size() && term[i + 1] == '\'') {
            oring = (oring || !(values[indx[term[i]]]));
            i++;
        }
        else {
            oring = (oring || values[indx[term[i]]]);
        }
    }
    return oring;
}


bool calculate_function(vector<bool> values, string s, map<char, int>indx)
{
    bool res;

    vector<string> terms;

    if (checkPOS(s)) { //PoS
        terms = separator_POS(s);
        res = 1;
        for (int i = 0; i < terms.size(); i++)
            res = (res && calculate_expression_POS(values, terms[i], indx));
        return res;

    }
    else { //SoP

        terms = separator_SOP(s);
        res = 0;
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


string bool_string(vector<bool> v)
{
    string result;
    for (int i = 0; i < v.size(); i++)
    {
        bool value = v[i];
        result.push_back(value ? '1' : '0');
    }
    return result;
}

vector<Implicant> settingToclass(map<int, vector<bool> > minterms)
{
    map<int, vector<bool> >::const_iterator it;
    Implicant m1;
    vector<Implicant> imp;

    for (it = minterms.begin(); it != minterms.end(); ++it)
    {
        Implicant m1;
        m1.indicies.push_back(it->first);
        m1.binary = bool_string(it->second);
        imp.push_back(m1);
    }

    return imp;
}

vector<Implicant> truth_table_generator(string s) {

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
        cout << calculate_function(values, s, indx) << endl;


        //##### Selecting minterms and maxterms ######
        if (calculate_function(values, s, indx))
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

    return settingToclass(minterms);

}

int countOnes(string binaryLiteral)
{
    int counter = 0;
    for (char c : binaryLiteral)
    {
        if (c == '1')
            counter++;
    }
    return counter;
}
string replace_diff(const string& literal1, const string& literal2)
{
    string new_num = "";
    for (int i = 0; i < literal1.size(); i++)
    {
        if (literal1[i] != literal2[i])
            new_num += '-';
        else
            new_num += literal1[i];
    }
    return new_num;
}
bool logic_diff(const string& a, const string& b)
{
    int count = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
        {
            count++;
            if (count > 1)
            {
                return false; // If more than one differing bit, return false
            }
        }
    }
    return (count == 1);
}

vector<vector<Implicant> > find_groups(vector<Implicant> Tawfik)
{

    vector<vector<Implicant> > v;

    for (const auto& it : Tawfik)
    {
        int num = countOnes(it.binary);
        if (num >= v.size())
        {
            v.resize(num + 1);
        }

        v[num].push_back(it);
    }
    return v;
}
vector<Implicant> handling(string str1, string str2, string new_binary, vector<Implicant> v1)
{
    bool found1 = false, found2 = false;
    vector<int> merged_vector;
    int pos1 = -1, pos2 = -1;
    bool exists = false;//to handle duplicates

    for (const auto& i : v1)
    {
        if (i.binary == new_binary)
        {
            exists = true;//if i find duplicates i mark their combine as true
        }
    }

    for (int i = 0; i < v1.size(); i++)
    {
        if (!found1 && v1[i].binary == str1)
        {
            pos1 = i;
            merged_vector.insert(merged_vector.end(), v1[i].indicies.begin(), v1[i].indicies.end());
            found1 = true;
        }
        if (!found2 && v1[i].binary == str2)
        {
            pos2 = i;
            merged_vector.insert(merged_vector.end(), v1[i].indicies.begin(), v1[i].indicies.end());
            found2 = true;
        }
    }

    if (found1 && found2)
    {
        v1[pos1].combine = true;
        v1[pos2].combine = true;
        //i check if they are not duplicates add their stuff
        if (!exists) {
            Implicant x;
            x.binary = new_binary;
            x.indicies = merged_vector;
            x.combine = false;
            v1.push_back(x);

        }
    }


    return v1;
}

vector<Implicant> prime_Impicants(vector<Implicant> Tawfik)
{

    vector<Implicant> extract_primes;
    size_t previousSize = 0;
    int count = 1;
    while (Tawfik.size() > 0)
    {
        vector<vector<Implicant> > res = find_groups(Tawfik);

        for (size_t i = 0; i < res.size() - 1; i++)
        {
            vector<Implicant>& row1 = res[i];
            vector<Implicant>& row2 = res[i + 1];
            for (size_t j = 0; j < row1.size(); j++)
            {
                for (size_t k = 0; k < row2.size(); k++)
                {
                    if (logic_diff(row1[j].binary, row2[k].binary))
                    {
                        string new_binary = replace_diff(row1[j].binary, row2[k].binary);
                        Tawfik = handling(row1[j].binary, row2[k].binary, new_binary, Tawfik);

                    }
                }
            }
        }

        // for (const auto &imp : Tawfik)
        // {
        //     cout << "{ ";
        //     for (const auto &index : imp.indicies)
        //     {
        //         cout << index << " ";
        //     }
        //     cout << "} /" << imp.binary << "/ " << imp.combine << endl;
        // }
        // cout << "----------------" << endl;
        //to delete already merged binaries
        // for (int i = 0; i < Tawfik.size();)
        // {
        //     if (Tawfik[i].combine == true)
        //     {
        //         Tawfik.erase(Tawfik.begin() + i);
        //     }
        //     else
        //     {
        //         i++;
        //     }
        // }
        //lw 7asel error men hena
        Tawfik.erase(
            std::remove_if(Tawfik.begin(), Tawfik.end(), [](const Implicant& imp) {
                return imp.combine; // removes all elements with combine == true
                }),
            Tawfik.end()
                    );



        // to extract prime implicants
        for (const auto& imp : Tawfik)
        {
            if (!imp.combine && imp.indicies.size() == count)
            {
                extract_primes.push_back(imp);
            }
        }

        //to delete prime_Impicants from Tawfik
    // for (int i = 0; i < Tawfik.size();)
    // {
    //     if (Tawfik[i].indicies.size() == count)
    //     {
    //         Tawfik.erase(Tawfik.begin() + i);
    //     }
    //     else
    //     {
    //         i++;
    //     }
    // }
    //lw 7asel error men hena
        Tawfik.erase(
            std::remove_if(Tawfik.begin(), Tawfik.end(), [count](const Implicant& imp) {
                return imp.indicies.size() == count;
                }),
            Tawfik.end()
                    );

        count *= 2;
    }


    return extract_primes;
}


vector<int>mintermsnotcoveredbyessential(vector<int>nano,vector<Implicant>primes)
{
    vector<int>p;
    vector<int>print;
    
    for(const auto &it:primes)
    {
        for (const auto &index : it.indicies)
        {
            p.push_back(index);
        }
    }
    for (const auto &item : p) {
        if (std::find(nano.begin(), nano.end(), item) == nano.end()) {
           print.push_back(item);
        }
    }
       std::sort(print.begin(), print.end());
       print.erase(std::unique(print.begin(), print.end()), print.end());

    return print;
    
}

string binaryToExpression(string s)
{
    string expression = "";
    for (int i = 0; i < s.size(); i++)
        if (s[i] != '-')
        {
            expression += ('a' + i);
            if (s[i] == '0')
                expression += "'";
        }
    return expression;
}



vector<int> findEssentialPrimeImplicants(vector<Implicant>& amal) {
    map<int, int> mintermCounts; // Map to store the minterm(s) (key) and how many of this minterm we have
    vector<int> essentialMintermsAmal;
    vector<int> test; // This was not used in the function. Do you need it?

    // Count occurrences of each minterm
    for (const Implicant& implicant : amal) {
        for (int index : implicant.indicies) {
            if (mintermCounts.find(index) == mintermCounts.end()) {
                mintermCounts[index] = 1;
            } else {
                mintermCounts[index]++;
            }
        }
    }

    cout << "\n Printing Essential Prime Implicants:\n";

    for (const Implicant& implicant : amal) {
        bool isEssential = false;

        for (int index : implicant.indicies) {
            if (mintermCounts[index] == 1) {
                isEssential = true;
                
                // Push all the indices from the implicant into essentialMintermsAmal
                essentialMintermsAmal.insert(essentialMintermsAmal.end(), implicant.indicies.begin(), implicant.indicies.end());
                
                // No need to keep checking other indices in the current implicant
                break;
            }
        }

      

        if (isEssential) {
            cout << binaryToExpression(implicant.binary) << endl;
        }
    }

    return essentialMintermsAmal;
}


// printing Kmaps
int Number_Literals(string str) {
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
    return count;
}

void Kmaps_print(string str, vector<int>minterms)
{
    //determine the size of the Kmap
    int numOfvariable = Number_Literals(str);
    string headers2[] = {"0", "1"};
    string headers4[] = {"00", "01", "11", "10"};
    if(numOfvariable>4 || numOfvariable<2 )
    {
        cout << "invalid input size!" << endl;
              return;
    }
    int row = -1, col = -1;
    if (numOfvariable == 2)
    {
        row = 2;
        col = 2;
    }
    else if (numOfvariable == 3)
    {
        row = 2;
        col = 4;
    }
    else
    {
        row = 4;
        col = 4;
    }
    int kmap[4][4] = { 0 };//intialize all the kmap with 0
    //this will make it 0,1,3,2, so on.
    int gray_code[4] = { 0,1,3,2 };
    for (int m : minterms)
    {
        int k = gray_code[m / col];//to determine row_postion, is the max number of col in the kmap
        int j = gray_code[m % col];//to determine col_postion
        kmap[k][j] = 1;//assign 1 to minterm in the kmap
    }

    cout << "\nPrinting The K-MAP:" << endl;

        // Print top header
        cout << "   ";  // For the side space
        if (col == 2) {
            for (int j = 0; j < col; j++) {
                cout << setw(2) << headers2[j] << " ";
            }
        } else if (col == 4) {
            for (int j = 0; j < col; j++) {
                cout << setw(2) << headers4[j] << " ";
            }
        }
        cout << endl;

        // Print K-map with side labels
        for (int i = 0; i < row; i++) {
            // Print side label
            if (row == 2) {
                cout << headers2[i] << "  ";
            } else if (row == 4) {
                cout << headers4[i] << "  ";
            }

            // Print K-map row
            for (int j = 0; j < col; j++) {
                cout << setw(2) << kmap[i][j] << " ";
            }
            cout << endl;
        }
    }
// to find minterms not in essential
vector<int> get_minterms(vector<Implicant>v)
{
    vector<int>x;

    for (const auto& implicant : v)
    {
        for (int index : implicant.indicies)
        {

            x.push_back(index);
        }

    }
    return x;
}
void print_primeImplicants(vector<Implicant>v)
{
    for (const auto& implicant : v)
    {
        cout << "Implicant: " << implicant.binary << " Indicies: ";
        for (int index : implicant.indicies)
        {
            cout << index << " ";

        }
        cout << "\n";
    }
}


void open_url(string url) {

#ifdef _WIN32
    // Windows command
    string command = "start " + url;
#elif _WIN64
    string command = "start " + url;
#elif _APPLE_
    // macOS command
    string command = "open " + url;
#elif _MACH_
    string command = "open " + url;
#else
    // Linux command
    string command = "xdg-open " + url;
#endif

    int result = system(command.c_str());
    if (result != 0) {
        cerr << "Failed to open browser" << endl;
    }

}
void display_circuit(string expression) {

    vector<string>s = separator_SOP(expression);  //separating the expression into individual terms
    const string url = "C:/Users/ahmed/OneDrive/Desktop/TAWFIK/UNI/fall2023/Digital_Design/Quine-McCluskey-minimizer/circuit.html";


    //standard initializtion (same for different expressions in sop)
    string taw =
        "<!DOCTYPE html>\n"
        "<html>\n"
        "<head>\n"
        "<title>Displaying Circuit</title>\n"
        "<script src=\"https://cdnjs.cloudflare.com/ajax/libs/wavedrom/3.1.0/skins/default.js\" type=\"text/javascript\"></script>\n"
        "<script src=\"https://cdnjs.cloudflare.com/ajax/libs/wavedrom/3.1.0/wavedrom.min.js\" type=\"text/javascript\"></script>\n"
        "</head>\n"
        "<body onload=\"WaveDrom.ProcessAll()\">\n"
        "<script type=\"WaveDrom\">\n"
        "{ assign:[\n"
        "  [\"out\",\n"
        "    [\"|\",\n";

    //plugging in the new expression
    for (int i = 0; i < s.size(); i++) {

        //if I have one literal in that term
        if (s[i].size() == 1) {
            taw.pop_back();
            taw += " \"";
            taw += s[i][0];
            taw += "\",\n";
        }
        else if (s[i].size() == 2 && s[i][1] == '\'') {    //if I have one literal in that term but it is iverted
            taw.pop_back();
            taw += " [\"~\", \"";
            taw += s[i][0];
            taw += "\"],\n";
        }
        else {                                  //if I have multiple literals in that term
            taw += "      [\"&\"";
            for (int j = 0; j < s[i].size(); j++) {
                if (j + 1 < s[i].size() && s[i][j + 1] == '\'') {
                    taw += ", [\"~\", \"";
                    taw += s[i][j];
                    taw += "\"]";
                    j++;
                }
                else {
                    taw += ", \"";
                    taw += s[i][j];
                    taw += "\"";
                }
            }
            taw += "],\n";
        }
    }

    //adjustments
    taw.pop_back();
    taw.pop_back();

    //standard things
    taw += "\n    ]\n"
        "  ]\n"
        "]}\n"
        "</script>\n"
        "<h1>Testing Circuit</h1>\n"
        "</body>\n"
        "</html>\n";

    // storing the new code into the html file (the same url)
    ofstream htmlFile(url);
    if (htmlFile.is_open()) {
        htmlFile << taw;
        htmlFile.close();
    }
    else
        cout << "Unable to open the file for writing." << endl;


    //opening this html file in the browser
    open_url(url);


}


void print_nonessentialminterms(vector<int>a)
{
    if(!a.empty())
    {
        for(int i=0; i<a.size(); i++)
        {
            cout << a[i] << " ";
        }
    }
    else
    {
        cout << "all the minterms are covered by essential!" << endl;
    }
}

vector<Implicant> findNonEssentialPrimeImplicants(const vector<int>& essentialMinterms, const vector<Implicant>& primeImplicants) {
    vector<Implicant> nonEssentialImplicants;

    for (const Implicant& implicant : primeImplicants) {
        bool isEssential = false;

        // Check if the implicant is essential (covers an essential minterm)
        for (int minterm : implicant.indicies) {
            if (find(essentialMinterms.begin(), essentialMinterms.end(), minterm) != essentialMinterms.end()) {
                isEssential = true;
                break;
            }
        }

        // If not essential, add the implicant to the non-essential list
        if (!isEssential) {
            nonEssentialImplicants.push_back(implicant);
        }
    }

    return nonEssentialImplicants;
}


vector<Implicant> remove_essential_primes_and_minterms(vector<int>&minterms, vector<Implicant>&primes,vector<int>essential_minterms, vector<int>essential_primes) {
    vector<Implicant>essential_prime_implicants;

    //delting the essential primes from the primes and the corresponding minterms
    for (int i = 0; i < essential_primes.size(); i++) {
        for (int j = 0; j < primes[i].indicies.size(); j++)
        {
           minterms.erase(remove(minterms.begin(), minterms.end(), primes[essential_primes[i]].indicies[j]), minterms.end());    //deleting from the minterms
        }
        essential_prime_implicants.push_back(primes[i]);
    }
    for (int j = 0; j < essential_primes.size(); j++)
    {
        primes.erase(remove(primes.begin(), primes.end(), primes[j]), primes.end());    //deleting from the minterms
    }
    return essential_prime_implicants;
     
}

void coverage_table(vector<int>minterms, vector<Implicant>primes) {

    map<int, int>unique;
    vector<int>essential_minterms;
    vector<int>essential_primes;
    vector<Implicant>essential_prime_implicants;

    //displaying the first table
    cout << "     ";
    for (int j = 0; j < minterms.size(); j++)
    {
        cout << " " << minterms[j] << " ";
    }
    cout << endl;
    for (int i = 0; i < primes.size(); i++)
    {
        cout << primes[i].binary << " ";
        for (int j = 0; j < minterms.size(); j++)
        {
            if (find(primes[i].indicies.begin(), primes[i].indicies.end(), minterms[j]) != primes[i].indicies.end()) {
                cout << " X ";
                if (unique.find(minterms[j]) == unique.end())
                    unique[minterms[j]] = i;
                else
                    unique[minterms[j]] = -1;
            }
            else
                cout << " O ";
        }
        cout << endl;
    }

    
    for (auto i = unique.begin(); i != unique.end();i++) {
        if (i->second != -1) {
            essential_minterms.push_back(i->first);
            essential_primes.push_back(i->second);
        }
    }
    essential_prime_implicants = remove_essential_primes_and_minterms(minterms, primes, essential_minterms, essential_primes);

    cout << endl;
    cout << "     ";
    for (int j = 0; j < minterms.size(); j++)
    {
        cout << setw(1) << " " << minterms[j] << " ";
    }

    cout << endl;
    for (int i = 0; i < primes.size(); i++)
    {
        cout << primes[i].binary << " ";
        for (int j = 0; j < minterms.size(); j++)
        {
            if (find(primes[i].indicies.begin(), primes[i].indicies.end(), minterms[j]) != primes[i].indicies.end()) {
                cout << setw(1) << " X ";
                if (unique.find(minterms[j]) == unique.end())
                    unique[minterms[j]] = i;
                else
                    unique[minterms[j]] = -1;
                            }
            else
                 cout << setw(1) << " O ";
        }
        cout << endl;
    }

    if (minterms.size() != 0 && primes.size()!=0) {
        //minterms = eliminateDominatedRows(primes);    // Error
        //primes = eliminateDominatingColumns(primes);
    }

    cout << "The minimized boolean expression is: ";
    for (int i = 0; i < essential_prime_implicants.size(); i++)
    {
        
        cout << binaryToExpression(essential_prime_implicants[i].binary) << "+";
    }
    cout << endl;

}
//we have two boolean functions that check if a row/column is dominated/dominating
//which we call in their respective comparisons 
bool isColumnDominating(Implicant imp1, Implicant imp2) //by comparing the binary representation for each implicant 
{
    const string& str1 = imp1.binary;
    const string& str2 = imp2.binary;

    for (size_t i = 0; i < str1.length(); i++) // check if the character in implicant1 is '1' and the character in implicant2 is '0'
    {
        if (str1[i] == '1' && str2[i] == '0') //if this is true this means it does not dominate 
        {
            return false;
        }
    }

    return true;//this means imp2 dominates imp1 
}

bool isRowDominated(const Implicant& imp1, const Implicant& imp2) //we can compare minterms here 
{
    for (int minterm1 : imp1.indicies) //loop through the first minterm and initialize the isCovered to false 
    {
        bool isCovered = false;

        for (int minterm2 : imp2.indicies) //loop through the second minterm we want to compare to the first minterm to check 
        {//if they are both the same (aka covered) 
            if (minterm1 == minterm2) //if both minterms are present in the same cover return true 
            {
                isCovered = true;
                break;
            }
        }

        if (!isCovered) {
            return false; //if any minterm of imp1 is not covered by imp2 then imp1 is not dominated 
        }
    }

    return true;
}

vector<Implicant> eliminateDominatingColumns(vector<Implicant> pi) //gets the prime implicant vector from amal 
{
    vector<Implicant> result;
    vector<bool> covered(pi.size(), false);

    for (size_t i = 0; i < pi.size(); i++) //loop through each PI 
    {
        for (size_t j = i + 1; j < pi.size(); j++) //compare the current implicant with others 
        {
            if (!covered[j] && isColumnDominating(pi[i], pi[j])) //check if the PI we are on is dominating or not
            {
                covered[j] = true; //if it is, add it to vector covered
            }
        }
    }

    for (size_t i = 0; i < pi.size(); i++)  // collect the non-covered prime implicants as they are not dominated
    {
        if (!covered[i])
        {
            result.push_back(pi[i]);
        }
    }

    return result;
}

vector<Implicant> eliminateDominatedRows(vector<Implicant> pi)// to loop through rows 
{
    vector<Implicant> result;

    for (size_t i = 0; i < pi.size(); i++) {
        bool isDominated = false;
        for (size_t j = 0; j < pi.size(); j++) {
            if (i != j && !pi[j].is_essential) {
                if (isRowDominated(pi[i], pi[j])) {
                    isDominated = true;
                    break;
                }
            }
        }

        if (!isDominated)
        {
            result.push_back(pi[i]);
        }
    }

    return result;
}
int main()
{
    string expression;
    //expression = "a'b'+ab+bc+a'c";
    //b+a'c
    cout << "Enter valid expression: " << '\n'; 
    cin >> expression; 
    bool flag = check(expression);

    if (flag == true) {
        vector<Implicant> Tawfik = truth_table_generator(expression);
        vector<int>minterms=get_minterms(Tawfik);
        
        
        vector<Implicant> primeImplicants = prime_Impicants(Tawfik);
        
        
        
        cout << endl << endl;
        cout << "primeImplicants: " << endl;
        print_primeImplicants(primeImplicants);
        
        vector<int> essentialMinterms = findEssentialPrimeImplicants(primeImplicants);
        
        cout<<"minterms not coverd by essentials:"<<endl;
        
        vector<int>m= mintermsnotcoveredbyessential(essentialMinterms, primeImplicants);
        print_nonessentialminterms(m);
        
        Kmaps_print(expression, minterms);
        
        
       cout << '\n';
       coverage_table(minterms, primeImplicants);
        
        
    }
   

    //display_circuit("a+b'");            //plug in the expression

    return 0;
}


