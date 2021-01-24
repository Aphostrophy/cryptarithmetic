#include <iostream>
#include <fstream>
#include <map> 
#include <chrono>
#include <vector>
#include <array>
#include <math.h>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace std::chrono;

typedef std::map<char, int> BooleanMap;

void reverse(int arr[],int start,int end){
    int temp;
    if(start<end){
        while(start<end){
            temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
        }
    }
}

int next_permute(int arr[],int size){
    int inv_point = size - 2;
    int temp;

    while(inv_point>=0 && arr[inv_point]>=arr[inv_point+1]){
        inv_point--;
    }
    if(inv_point<0){
        return 0;
    }
    for(int i=size-1;i>inv_point;--i){
        if(arr[i]>arr[inv_point]){
            temp = arr[i];
            arr[i] = arr[inv_point];
            arr[inv_point] = temp;
            break;
        }
    }
    reverse(arr,inv_point+1,size-1);
    return 1;
}

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

bool permute(int combinations[],vector<string> operands,BooleanMap &variables, int &counter, int size){
    int i;
    do{
        i = 0;
        counter++;
        for (auto const& p : variables)
        {
            variables[p.first] = combinations[i];
            i++;
        }
        if(isValid(operands,variables)){
            return true;
        }
    } while(next_permute(combinations,size));

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

        bool found=false;
        int counter=0;

        int v[10] ={0}; //bitmask
        int combinations[variables.size()];
        for(int i=10;i>10-variables.size();--i){
            v[i] = 1;
        }

        int t;

        operands[operands.size()-3].pop_back(); //Removes the + sign

        auto start = high_resolution_clock::now();

        do {
            t=0;
            for (int i = 0; i < 10; ++i) {
                if (v[i]) {
                    combinations[t]=i;
                    t++;
                }
            }
            if(permute(combinations,operands,variables,counter,variables.size())){
                found = true;
                break;
            }
        } while(next_permute(v,10));

        if(found){
            for ( const auto &pair : variables ) {
                cout << pair.first << " : " << pair.second << "\n";
            }

            for(int i=0;i<operands.size();i++){
                cout << operands[i] << " : " << subtituteOperandsToInt(operands[i],variables) << "\n";
            }
        } else{
            cout << "No solutions found" << "\n";
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        cout << "Time taken for brute force : " << duration.count() << " milliseconds" << "\n";
        cout << "Jumlah tes : " << counter << "\n";

        cout << "---------------" << endl;

    } // END OF ELSE STATEMENT

    arith_file.close();
    return 0;
}