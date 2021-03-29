/*
 * @lc app=leetcode.cn id=118 lang=cpp
 *
 * [118] 杨辉三角
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if (numRows < 1) return {};
        vector<vector<int>> ret{ {1} };
        while(ret.size()<numRows){
            vector<int> temp{ 1 };
            for (vector<int>::iterator i = ret.back().begin(); i + 1 != ret.back().end(); ++i)
                temp.push_back(*i + *(i + 1));
            temp.push_back(1);
            ret.push_back(temp);
        }
        return ret;
    }
};
// @lc code=end

