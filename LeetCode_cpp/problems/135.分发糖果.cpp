/*
 * @lc app=leetcode.cn id=135 lang=cpp
 *
 * [135] 分发糖果
 */
#include <numeric>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    int candy(vector<int>& ratings) {
        minnum.assign(ratings.begin(), ratings.end());
        check.assign(ratings.size(), 0);
        int ret = 0;
        for (vector<bool>::size_type i = 0; i < check.size(); ++i) {
            ret += minmize(ratings, i);
        }
        return ret;
    }

  private:
    vector<bool> check;
    vector<int>  minnum;

    int minmize(vector<int>& ratings, vector<int>::size_type pos) {
        if (!check[pos]) {
            int left, right;
            if (pos == 0)
                left = 1;
            else
                left = ratings[pos - 1] < ratings[pos] ? minmize(minnum, pos - 1) + 1 : 1;
            if (pos == ratings.size() - 1)
                right = 1;
            else
                right = ratings[pos + 1] < ratings[pos] ? minmize(minnum, pos + 1) + 1 : 1;
            minnum[pos] = fmax(left, right);
            check[pos]  = 1;
        }
        return minnum[pos];
    }
};
// @lc code=end
