/*
 * @lc app=leetcode->cn id=684 lang=cpp
 *
 * [684] 冗余连接
 */
#include <map>
#include <set>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
    friend struct point;

  public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        for (const auto& r : edges) {
            if (makepoint(r.front(), r.back()))
                continue;
            else
                return r;
        }
        return {};
    }

  private:
    struct point
    {
        int id;
        int connect;
        point(int i, int c) : id(i), connect(c) {}
        int& root(map<int, point*>& table) {
            if (connect != table[connect]->connect) {
                connect = table[connect]->root(table);
            }
            return connect;
        }
    };
    bool makepoint(int id1, int id2) {
        if (table.count(id1) && table.count(id2)) {
            if (table[id1]->root(table) != table[id2]->root(table)) {
                table[table[id2]->root(table)]->root(table) = table[id1]->root(table);
                return 1;
            }
            else
                return 0;
        }
        else if (table.count(id1))
            table[id2] = new point(id2, id1);
        else if (table.count(id2))
            table[id1] = new point(id1, id2);
        else {
            table[id1] = new point(id1, id1);
            table[id2] = new point(id2, id1);
        }
        return 1;
    }
    map<int, point*> table;
};
// @lc code=end
