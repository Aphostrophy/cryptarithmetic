#include <bits/stdc++.h>

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

int next_permutation(int arr[],int size){
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

int main(){
    int arr[3] = {0,1,1};
    do{
        for(int i=0;i<3;i++){
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    } while(next_permutation(arr,3));
    return 0;
}