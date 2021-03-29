/*
 * @lc app=leetcode.cn id=738 lang=cpp
 *
 * [738] 单调递增的数字
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    int monotoneIncreasingDigits(int N) {
        int         ret = N;
        vector<int> digit;
        digit.push_back(N % 10);
        N /= 10;
        int lastincrease = -1, changedigit = -1;
        while (N > 0) {
            int tem = N % 10;
            if (digit.back() < tem) {
                lastincrease = digit.size();
                changedigit  = -1;
            }
            if (lastincrease != -1 && changedigit == -1 && digit.back() > tem) changedigit = digit.size() - 1;
            digit.push_back(tem);
            N /= 10;
        }
        if (lastincrease != -1) {
            ret = 0;
            if (changedigit == -1) {
                ret += digit.back() - 1;
                for (vector<int>::size_type i = 0; i < digit.size() - 1; ++i) ret = ret * 10 + 9;
            }
            else {
                for (vector<int>::size_type i = digit.size() - 1; i != vector<int>::size_type(-1); --i) {
                    if (i > changedigit)
                        ret = ret * 10 + digit[i];
                    else if (i == changedigit)
                        ret = ret * 10 + digit[i] - 1;
                    else
                        ret = ret * 10 + 9;
                }
            }
        }
        return ret;
    }
};
// @lc code=end

