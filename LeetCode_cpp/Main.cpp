#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    Solution s;

    vector<vector<int>> pairs{
        { 1, 2 },
        { 1, 3 },
        { 2, 3 }
    };
    s.findRedundantConnection(pairs);
}
