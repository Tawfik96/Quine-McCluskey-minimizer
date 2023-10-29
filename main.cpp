#include <iostream>
#include <string>
#include <map>
#include<cmath>
#include<algorithm>
#include <vector>


using namespace std;
class Implicant
{
public:
    vector<int> indicies;
    string binary;
    bool combine = false;

   // Implicant(const vector<int>& indices, const string& binary) : indicies(indicies), binary(binary) {}

};
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



//void display( vector<bool> k) {
//    for (int i = 0; i < k.size(); i++) {
//        cout << k[i] << ",";
//    }
//}

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
string replace_diff(const string &literal1, const string &literal2)
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
bool logic_diff(const string &a, const string &b)
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
vector<vector<Implicant> > find_groups(vector<Implicant> Tawfik)
{

    vector<vector<Implicant> > v;

    for (const auto &it : Tawfik)
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

    for (const auto &i : v1)
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
        if(!exists){
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
            vector<Implicant> &row1 = res[i];
            vector<Implicant> &row2 = res[i + 1];
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
            for (const auto &imp : Tawfik)
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

        count *=2;
    }

  
    return extract_primes;
}

vector<bool> dec_bin(int num, int num_of_bits)
{
    vector<bool> binary_values;
    int temp = 0;
    int i = 0;
    while (num > 0)
    {

        // storing remainder in binary array
        binary_values.push_back(num % 2);
        num = num / 2;
        i++;
    }
    while (i < num_of_bits)
    { // continuer the remaining places with zeros
        binary_values.push_back(0);
        i++;
    }
    // Inveting the order of the array so that it match the order of the literals.
    reverse(binary_values.begin(), binary_values.end());
    return binary_values;
}
void print_minterms(vector<int>nano,vector<Implicant>primes)
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
     for(int i=0;i<print.size();i++)
     cout<<print[i]<<" ";
     cout<<endl;
    
    
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
    map<int, int> mintermCounts; //map to store the minterm(s) (key) and how many of this minterm we have 
    vector<int> essentialMintermsAmal; 
 
    for (const Implicant& implicant : amal) //loop through the Amal vector 
    {
        for (int index : implicant.indicies) //loop through the vector that has the minterms 
        {
            if (mintermCounts.find(index) == mintermCounts.end()) // if a minterm is not in the map, 
            {
                mintermCounts[index] = 1; //it is initialized with a count of 1, meaning it's unique.
            }
            else 
            {
                mintermCounts[index]++;//if it's already in the map, its count is incremented
            }
        }
    }

    //printing 
    for (const Implicant& implicant : amal) //loop through PI amal
    {
        bool isEssential = false;

        for (int index : implicant.indicies) //loop through the minterms again
        {
            if (mintermCounts[index] == 1) //if they have a count = 1 then they are covered only once 
            {
                isEssential = true; //flag is set to true, meaning this minterm exists only once
                essentialMintermsAmal.push_back(index);
                //break;
            }
        }
        if (isEssential) //and this minterm goes here and is printed 
        {
            //cout << "Essential Prime Implicant as binary: " << implicant.binary << endl; //doctor msh 3ayezha 
            cout << "Essential Prime Implicant as expression: " << binaryToExpression(implicant.binary) << endl;
        }
    }
    return essentialMintermsAmal; //returns vector<int> that has the minterms covered by essential PIs 
}

//printing Kmaps
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
    int numOfvariable=Number_Literals(str);
    int row=-1,col=-1;
    if(numOfvariable==2)
    {
        row=2;
        col=2;
    }
    else if(numOfvariable==3)
    {
        row=2;
        col=4;
    }
    else
    {
        row=4;
        col=4;
    }
    int kmap[4][4] = {0};//intialize all the kmap with 0
    //this will make it 0,1,3,2, so on.
    int gray_code[4]={0,1,3,2};
     for(int m:minterms)
     {
         int k=gray_code[m/col];//to determine row_postion, is the max number of col in the kmap
         int j=gray_code[m%col];//to determine col_postion
         kmap[k][j]=1;//assign 1 to minterm in the kmap
     }
     cout<<"printing the kmap:"<<endl;
     
     for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << setw(2) << kmap[i][j] << " ";
        }
       cout << endl;
    }
    
}

int main()
{
    string expression;
    expression = "ac'+ab";
    ////cout << check(expression);
    string s = "(a+b)(b+c)";
    truth_table_generator(s);
    map<int, vector<bool> > minterms;
    
    minterms[10]=dec_bin(10,6);
    minterms[18] = dec_bin(18,6);
    minterms[26] = dec_bin(26,6);
    minterms[40]=dec_bin(40,6);
    minterms[41]=dec_bin(41,6);
    minterms[42]=dec_bin(42,6);
    minterms[48]=dec_bin(48,6);
    minterms[49]=dec_bin(49,6);
    minterms[50]=dec_bin(50,6);
    minterms[52]=dec_bin(52,6);
    minterms[53]=dec_bin(53,6);
    minterms[56]=dec_bin(56,6);
    minterms[57]=dec_bin(57,6);
    minterms[60]=dec_bin(60,6);
    minterms[61]=dec_bin(61,6);

    vector<Implicant> Tawfik = settingToclass(minterms);
    vector<Implicant> primeImplicants = prime_Impicants(Tawfik);
    vector<int>test_kmap;
    for (const auto &implicant : primeImplicants)
    {
        cout << "Implicant: " << implicant.binary << " Indices: ";
        for (int index : implicant.indicies)
        {
            cout << index << " ";
            test_kmap.push_back(index);
        }
        cout << "\n";
    }
    
    cout<<"--------------"<<endl;
    vector<int>v={48,49,52,53,56,57,60,61};
    print_minterms(v,primeImplicants);

    //testing nano's function
    // vector<Implicant> implicants;
    // implicants.push_back({ {1, 2}, "110", false });
    // implicants.push_back({ {4, 5}, "101", false });
    // implicants.push_back({ {1, 4}, "100", false });
    // implicants.push_back({ {2, 5}, "010", false });
    // implicants.push_back({ {3}, "001", false });
    // implicants.push_back({ {6,5,1}, "111", false });


    vector<int> essentialMinterms = findEssentialPrimeImplicants(primeImplicants);

    // //findEssentialPrimeImplicants(implicants);
    // /*cout << "Essential Prime Implicants' Minterms:" << endl;
    // for (int minterm : essentialMinterms) {
    //     cout << minterm << " ";
    // }*/
     cout << endl;

   Kmaps_print(s, test_kmap);

    return 0;
}

