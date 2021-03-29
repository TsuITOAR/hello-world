/*
 * @lc app=leetcode.cn id=321 lang=cpp
 *
 * [321] 拼接最大数
 */
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution
{
public:
    vector<int> maxNumber(vector<int> &nums1, vector<int> &nums2, int k)
    {
        auto ret = assembleMaxNumber(nums1, nums2, 0, 0, k);
        reverse(ret.begin(), ret.end());
        return ret;
    }

private:
    vector<int> assembleMaxNumber(vector<int> &nums1, vector<int> &nums2, vector<int>::size_type start1, vector<int>::size_type start2, int k)
    {
        cout << start1 << ',' << start2 << ',' << k << endl;
        if (ans.find({{start1, start2}, k}) != ans.end())
            return ans[{{start1, start2}, k}];
        auto &an = ans[{{start1, start2}, k}];
        if (nums1.size() - start1 + nums2.size() - start2 < k)
            an.push_back(-1);
        if (!an.empty() || k == 0)
            return an;

        vector<int> temp1, temp2;
        for (int i = 9; i >= 0; --i)
        {
            for (auto cur1 = start1; cur1 < nums1.size(); ++cur1)
            {
                if (nums1[cur1] == i)
                {
                    temp1 = assembleMaxNumber(nums1, nums2, cur1 + 1, start2, k - 1);
                    temp1.push_back(i);
                    break;
                }
            }
            for (auto cur2 = start2; cur2 < nums2.size(); ++cur2)
            {
                if (nums2[cur2] == i)
                {
                    temp2 = assembleMaxNumber(nums1, nums2, start1, cur2 + 1, k - 1);
                    temp2.push_back(i);
                    break;
                }
            }
            an = myfmax(temp1, temp2);
            if (an.empty())
                continue;
            else
            {
                if (an.front() != -1)
                {
                    for (const auto &r : an)
                        cout << r << ',';
                    cout << endl;
                    return an;
                }
                else
                {
                    an.clear();
                    temp1.clear();
                    temp2.clear();
                }
            }
        }
        an = {-1};
        return an;
    }
    vector<int> &myfmax(vector<int> &v1, vector<int> &v2)
    {
        vector<int>::reverse_iterator it1 = v1.rbegin(), it2 = v2.rbegin();
        while (it1 != v1.rend() || it2 != v2.rend())
        {
            if (it1 == v1.rend())
                return v2;
            else if (it2 == v2.rend())
                return v1;
            if (*it1 > *it2)
                return v1;
            else if (*it1 < *it2)
                return v2;
            ++it1;
            ++it2;
        }
        return v1;
    }
    typedef pair<vector<int>::size_type, vector<int>::size_type> coor;
    map<pair<coor, int>, vector<int>> ans;
};
// @lc code=end

