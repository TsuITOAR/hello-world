/*
 * @lc app=leetcode.cn id=103 lang=cpp
 *
 * [103] 二叉树的锯齿形层次遍历
 */

#include <vector>
using namespace std;
struct TreeNode
{
    int       val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// @lc code=start

class Solution
{
  public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> ret;
        vector<TreeNode*>   last{root};
        while (!last.empty()) {
            ret.push_back({});
            for(auto const&r:last){
                ret.back().push_back(r->val);
            }
            vector<TreeNode*> tem;
            if (ret.size() % 2) {
                for (auto it = last.rbegin(); it != last.rend(); ++it) {
                    if ((*it)->right) tem.push_back((*it)->right);
                    if ((*it)->left) tem.push_back((*it)->left);
                }
            }
            else {
                for (auto it = last.rbegin(); it != last.rend(); ++it) {
                    if ((*it)->left) tem.push_back((*it)->left);
                    if ((*it)->right) tem.push_back((*it)->right);
                }
            }
            swap(tem, last);
        }
        return ret;
    }
};
// @lc code=end
