#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

typedef std::map<char, int> BooleanMap;

bool isEqual(){

    return true;
}

int stringToInt(string str,BooleanMap variables){
    int sum = 0;
    for(int i=0;i < str.size();i++){
        sum += variables[str[i]]*pow(10,str.size()-i);
    }
    return sum;
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
            variables[line[0]] = 1; //Assume first letter can't be zero
            //Erases useless symbols
            variables.erase('-');
            variables.erase('+');
        }
        cout << endl;
        for ( const auto &pair : variables ) {
            cout << pair.first << " : " << pair.second << "\n";
        }

        operands[operands.size()-3].pop_back(); //Removes the + sign
        for(int i=0;i<operands.size();i++){
            cout << operands[i] << " : " << stringToInt(operands[i],variables) << "\n";
        }
    }
    
    arith_file.close();
    return 0;
}