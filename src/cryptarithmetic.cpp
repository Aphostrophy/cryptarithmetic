#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <math.h>
#include <iomanip>
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
            cout << line << endl;
            operands.push_back(line);
            for(char &c : line){
                cout << c << endl;
                if(!variables.count(c)){
                    variables[c] = 0;
                }
            }
            //Erases useless symbols
            variables.erase('-');
            variables.erase('+');
        }
        cout << endl;
        string source = "";
        for ( const auto &pair : variables ) {
            cout << pair.first << " : " << pair.second << "\n";
            source.append(to_string(pair.second));
        }

        cout << source << endl;

        operands[operands.size()-3].pop_back(); //Removes the + sign
        for(int i=0;i<operands.size();i++){
            cout << operands[i] << " : " << subtituteOperandsToInt(operands[i],variables) << "\n";
        }

        cout << "---------------" << endl;

        int trueLength = source.size();

        while(stoi(source)<pow(10,trueLength)){
            int mapIndex=0;
            for ( const auto &pair : variables ) {
                variables[pair.first] = (int)source[mapIndex] - 48;
                mapIndex++;
            }
            // for(int i=0;i<operands.size();i++){
            //     cout << operands[i] << " : " << subtituteOperandsToInt(operands[i],variables) << "\n";
            // }
            if(isValid(operands,variables)){
                cout << "FOUND IT" << endl;
                break;
            }
            // cout << endl;
            stringstream ss;
            ss << std::setfill('0') << std::setw(trueLength) << to_string(stoi(source)+1);
            source = ss.str();
        }

        for(int i=0;i<operands.size();i++){
            cout << operands[i] << " : " << subtituteOperandsToInt(operands[i],variables) << "\n";
        }

    } // END OF ELSE STATEMENT

    arith_file.close();
    return 0;
}