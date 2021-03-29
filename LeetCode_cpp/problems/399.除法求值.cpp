/*
 * @lc app=leetcode.cn id=399 lang=cpp
 *
 * [399] 除法求值
 */
#include <map>
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        valsinfo.clear();
        for (vector<double>::size_type i = 0; i < equations.size(); ++i) {
            addtoalpha(equations[i], values[i]);
        }
        vector<double> ret;
        for (const auto& r : queries) ret.push_back(solve(r));
        return ret;
    }

  private:
    struct alpha
    {
        alpha(string ro, double ra) : roo(ro), rate(ra) {}

        double& value(Solution* sptr) {
            if (sptr->valsinfo[roo]->roo != roo) {
                rate = rate * (sptr->valsinfo[roo]->value(sptr));
                roo  = sptr->valsinfo[roo]->root(sptr);
            }
            return rate;
        }

        string& root(Solution* sptr) {
            if (sptr->valsinfo[roo]->roo != roo) {
                rate = rate * (sptr->valsinfo[roo]->value(sptr));
                roo  = sptr->valsinfo[roo]->root(sptr);
            }
            return roo;
        }

      private:
        string roo;
        double rate;
    };
    void addtoalpha(vector<string> equ, double value) {
        auto &a = equ.front(), &b = equ.back();
        if (!valsinfo.count(a) && !valsinfo.count(b)) {
            valsinfo[a] = new alpha(b, value);
            valsinfo[b] = new alpha(b, 1);
        }
        else if (!valsinfo.count(b)) {
            valsinfo[b] = new alpha(a, 1 / value);
        }
        else if (!valsinfo.count(a)) {
            valsinfo[a] = new alpha(b, value);
        }
        else {
            valsinfo[valsinfo[a]->root(this)]->value(this) = valsinfo[b]->value(this) * value / valsinfo[a]->value(this);
            valsinfo[valsinfo[a]->root(this)]->root(this)  = valsinfo[valsinfo[b]->root(this)]->root(this);
        }
    }
    double solve(vector<string> que) {
        if (valsinfo.count(que[0]) && valsinfo.count(que[1]) && valsinfo[que[0]]->root(this) == valsinfo[que[1]]->root(this)) {
            return valsinfo[que[0]]->value(this) / valsinfo[que[1]]->value(this);
        }
        else
            return -1;
    }

    map<string, alpha*> valsinfo;
};
// @lc code=end
