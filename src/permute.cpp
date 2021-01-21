#include <iostream>
#include <algorithm>
#include <vector>

void permute(std::vector<int> combinations,int r){
    do{
        for(int i=0; i < r;++i){
            std::cout << combinations.at(i) << " ";
        }
        std::cout << "\n";
    } while(std::next_permutation(combinations.begin(), combinations.end()));
}

int main() {
    int n, r;
    std::cin >> n;
    std::cin >> r;

    std::vector<bool> v(n);
    std::vector<int> combinations(r);
    std::fill(v.end() - r, v.end(), true);

    int t;

    do {
        t=0;
        for (int i = 0; i < n; ++i) {
            if (v[i]) {
                combinations.at(t)=i;
                t++;
            }
        }
        permute(combinations, r);
    } while (std::next_permutation(v.begin(), v.end()));
    return 0;
}