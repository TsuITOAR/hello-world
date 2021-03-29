/*
 * @lc app=leetcode.cn id=973 lang=cpp
 *
 * [973] 最接近原点的 K 个点
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        if (points.size() <= K) {
            sort(
                points.begin(), points.end(), [this](const vector<int>& a, const vector<int>& b) { return dist(a) < dist(b); });
            return points;
        }
        vector<vector<int>>::iterator begin = points.begin();
        vector<vector<int>>::iterator end   = points.end();
        vector<vector<int>>::iterator mid   = begin + (end - begin) / 2;
        vector<vector<int>>           leftpart{ begin, mid };
        vector<vector<int>>           rightpart{ mid, end };
        leftpart  = kClosest(leftpart, K);
        rightpart = kClosest(rightpart, K);
        vector<vector<int>>           ret;
        vector<vector<int>>::iterator j = leftpart.begin(), k = rightpart.begin();
        for (int i = 0; i < K; ++i) {
            if (j == leftpart.end() && k == rightpart.end()) {
                cout << "Erro" << endl;
                return points;
            }
            if (j == leftpart.end()) {
                ret.push_back(*(k++));
                continue;
            }
            if (k == rightpart.end()) {
                ret.push_back(*(j++));
                continue;
            }
            if (dist(*j) > dist(*k))
                ret.push_back(*(k++));
            else
                ret.push_back(*(j++));
        }
        return ret;
    }
    double dist(const vector<int>& a) { return sqrt(a[0] * a[0] + a[1] * a[1]); }
};
// @lc code=end
