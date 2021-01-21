#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <math.h>
#include <iomanip>
#include <algorithm>

using namespace std;

typedef std::map<char, int> BooleanMap;

int subtituteOperandsToInt(string str,BooleanMap variables){
    int sum = 0;
    for(int i=0;i < str.size();i++){
        sum += variables[str[i]]*pow(10,str.size()-i-1);
    }
    return sum;
}

bool isValid(vector<string> operands,BooleanMap variables){
    int sum=0;

    for(int i=0;i<operands.size();i++){
        if(operands[i][0] != '-' && variables[operands[i][0]]==0){ // If first letter of a word is zero we assume it's false
            return false;
        }
        if(i<operands.size()-2){
            sum += subtituteOperandsToInt(operands[i],variables);
        }
    }

    return sum == subtituteOperandsToInt(operands[operands.size()-1], variables);
}

bool permute(std::vector<int> combinations,vector<string> operands,BooleanMap &variables){
    int i;
    do{
        i = 0;
        for (auto const& p : variables)
        {
            variables[p.first] = combinations.at(i);
            i++;
        }
        if(isValid(operands,variables)){
            return true;
        }
    } while(std::next_permutation(combinations.begin(), combinations.end()));

    return false;
}


int main(){
    fstream arith_file;
    string file_name;

    BooleanMap variables;
    vector<string> operands;

    cin >> file_name;
    arith_file.open(file_name, ios::in);
    if(!arith_file){
        cout << "File not found!";
    } else{
        string line;

        while(getline(arith_file,line)){
            operands.push_back(line);
            for(char &c : line){
                if(!variables.count(c)){
                    variables[c] = 0;
                }
            }
            //Erases useless symbols
            variables.erase('-');
            variables.erase('+');
        }

        vector<bool> v(10);
        vector<int> combinations(variables.size());
        fill(v.end() - variables.size(), v.end(), true);

        int t;

        operands[operands.size()-3].pop_back(); //Removes the + sign

        for ( const auto &pair : variables ) {
            cout << pair.first << " : " << pair.second << "\n";
        }

        do {
            t=0;
            for (int i = 0; i < 10; ++i) {
                if (v[i]) {
                    combinations.at(t)=i;
                    t++;
                }
            }
            if(permute(combinations,operands,variables)){
                break;
            }
        } while (std::next_permutation(v.begin(), v.end()));

        cout << "---------------" << endl;

        for ( const auto &pair : variables ) {
            cout << pair.first << " : " << pair.second << "\n";
        }

        for(int i=0;i<operands.size();i++){
            cout << operands[i] << " : " << subtituteOperandsToInt(operands[i],variables) << "\n";
        }

    } // END OF ELSE STATEMENT

    arith_file.close();
    return 0;
}