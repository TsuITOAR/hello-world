/*
 * @lc app=leetcode.cn id=514 lang=cpp
 *
 * [514] 自由之路
 */

// @lc code=start
/*
* vector数组内存占用大
class Solution {
public:
    int findRotateSteps(string ring, string key) {
        return RotateSteps(ring, key, 0, 0);
    }
private:
    int dis(int start, int end, int size) {
        return min(abs(start - end), size - (abs(start - end)));
    }
    int RotateSteps(const string& ring, const string& key, int pos, int i) {
        if (i >= key.size()) return 0;
        if (ans[pos][i] != 0) return ans[pos][i];
        int tem = INT_MAX;
        if (ring[pos] == key[i]) tem = 1 + RotateSteps(ring, key, pos, i + 1);
        else {
            for (int j = 0; j < ring.size(); ++j) {
                if (ring[j] == key[i]) tem = min(tem, 1 + dis(pos, j, ring.size()) + RotateSteps(ring, key, j, i + 1));
            }
        }
        ans[pos][i] = tem;
        return tem;
    }
};
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Solution
{
  public:
    int findRotateSteps(string ring, string key) {
        int ch[26] = {0};
        for (int i = 0; i < ring.size(); ++i)
            harsh[ring[i] - 'a'][ch[ring[i] - 'a']++] = i;
        for (int i = 0; i < 26; ++i)
            harsh[i][ch[i]] = -1;
        return RotateSteps(ring, key, 0, 0);
    }

  private:
    static const int len           = 101;
    int              ans[len][len] = {0};
    int              harsh[26][len];
    int              dis(int start, int end, int size) { return min(abs(start - end), size - (abs(start - end))); }

    int RotateSteps(const string& ring, const string& key, int pos, int i) {
        if (i >= key.size())
            return 0;
        if (ans[pos][i] != 0)
            return ans[pos][i];
        int tem = INT_MAX;
        if (ring[pos] == key[i])
            tem = 1 + RotateSteps(ring, key, pos, i + 1);
        else {
            for (int j = 0; harsh[key[i] - 'a'][j] != -1; ++j) {
                tem = min(tem, 1 + dis(pos, harsh[key[i] - 'a'][j], ring.size()) + RotateSteps(ring, key, harsh[key[i] - 'a'][j], i + 1));
            }
        }
        ans[pos][i] = tem;
        return tem;
    }
};
// @lc code=end
