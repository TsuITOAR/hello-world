/*
 * @lc app=leetcode.cn id=605 lang=cpp
 *
 * [605] 种花问题
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        if (n == 0) return 1;
        for (auto it = flowerbed.begin(); it != flowerbed.end();) {
            if(*it == 1)
                ++it;
            auto ed = it;
            while (ed != flowerbed.end() && *ed == 0) ++ed;
            int tem = ed - it;
            if (it != flowerbed.begin()) --tem;
            if (ed != flowerbed.end()) --tem;
            if (tem > 0) {
                n -= tem / 2 + tem % 2;
                if (n <= 0) return 1;
            }
            it = ed;
        }
        return 0;
    }
};
// @lc code=end
