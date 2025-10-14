#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>
using namespace std;

// Function to print the 2D vector of blocks
void printBlocks(const std::vector<std::vector<int>>& blocks) {
    std::cout << "\nDetected Permutation Blocks (2D Array):" << std::endl;
    for (const auto& block : blocks) {
        std::cout << "[ ";
        for (int val : block) {
            std::cout << val << " ";
        }
        std::cout << "]" << std::endl;
    }
}

int main() {
    // The array from your test case
    std::vector<int> arr = {4, 1, 2, 3, 4, 5, 1, 2, 3, 8, 1, 2, 3, 4, 5, 6, 7};

    std::cout << "Input Array:" << std::endl;
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::vector<std::vector<int>> blocks_in_reverse;
    int n = arr.size();
    int limit = 1, st = 0;
    vector<int> cur;
    for(int i=0;i<n;i++){
        if(i==limit+1){
            blocks_in_reverse.push_back(cur);
            cur.clear();
            st = i;
        }
        limit = max(limit,arr[i]+st-1);
        cur.push_back(arr[i]);
    }
    blocks_in_reverse.push_back(cur);
    
    printBlocks(blocks_in_reverse);

    return 0;
}