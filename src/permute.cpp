#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>

using namespace std::chrono;

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

    auto start = high_resolution_clock::now();

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

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);

    std::cout << "Time taken for brute force : " << duration.count() << " seconds" << "\n";

    return 0;
}