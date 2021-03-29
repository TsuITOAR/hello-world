/*
 * @lc app=leetcode.cn id=860 lang=cpp
 *
 * [860] 柠檬水找零
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;
        for (const auto& r : bills) {
            if (r == 5) {
                ++five;
            }
            else {
                if (r == 10) {
                    ++ten;
                    --five;
                }
                else if (r == 20) {
                    if (ten > 0) {
                        --ten;
                        --five;
                    }
                    else
                        five -= 3;
                }
                if (five < 0 || ten < 0) return 0;
            }
        }
        return 1;
    }
};
// @lc code=end
