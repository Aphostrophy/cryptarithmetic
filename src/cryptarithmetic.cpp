#include <iostream>
#include <fstream>
#include <map>
using namespace std;

typedef std::map<char, char> BooleanMap;

int main(){
    fstream arith_file;
    string file_name;

    BooleanMap variables;

    cin >> file_name;
    arith_file.open(file_name, ios::in);
    if(!arith_file){
        cout << "File not found!";
    } else{
        string line;

        while(getline(arith_file,line)){
            cout << line << endl;
            cout << line.length() << endl;
            for(char &c : line){
                cout << c << endl;
                if(!variables.count(c) && c!='+' && c!='-'){
                    variables[c] = 0;
                }
            }
        }
        cout << endl;
        for ( const auto &pair : variables ) {
            cout << pair.first << "\n";
        }
    }
    arith_file.close();
    return 0;
}