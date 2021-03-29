/*
 * @lc app=leetcode.cn id=1203 lang=cpp
 *
 * [1203] 项目管理
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
    }

  private:
    struct item
    {
        item(int i, int g, vector<item*> d) : id(i), group(g), dependency(d){};
        int           id;
        int           group;
        vector<item*> dependency;
    };
    item* makeitem(int i,vector<int>& group, vector<vector<int>>& beforeItems) {
        if (beforeItems[i].empty()) return new item(i, group[i], {});
        vector<item*> depend;
        for(const auto&r:beforeItems[i]){
            depend.push_back(makeitem(r, group, beforeItems));
        }
        return new item(i, group[i], depend);
    }
};
// @lc code=end
