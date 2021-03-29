/*
 * @lc app=leetcode.cn id=1202 lang=cpp
 *
 * [1202] 交换字符串中的元素
 */
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        list<multiset<char>>         elem;
        list<set<string::size_type>> pos;

        map<int, decltype(elem)::iterator> elemharsh;
        map<int, decltype(pos)::iterator>  posharsh;
        for (const auto& r : pairs) {
            auto r1 = r.front(), r2 = r.back();
            if (r1 == r2) continue;
            auto el1 = elemharsh.find(r1), el2 = elemharsh.find(r2);
            auto po1 = posharsh.find(r1), po2 = posharsh.find(r2);
            if (po1 != posharsh.end() && po2 != posharsh.end()) {
                auto p1 = po1->second, p2 = po2->second;
                auto e1 = el1->second, e2 = el2->second;
                if (p1 == p2) continue;
                if (p1->size() < p2->size()) {
                    swap(p1, p2);
                    swap(e1, e2);
                    swap(r1, r2);
                }
                e1->insert(e2->begin(), e2->end());
                p1->insert(p2->begin(), p2->end());
                for (auto it = p2->begin(); it != p2->end(); ++it) {
                    posharsh[*it]  = posharsh[r1];
                    elemharsh[*it] = elemharsh[r1];
                }
                elem.erase(e2);
                pos.erase(p2);
            }
            else if (po1 != posharsh.end()) {
                el1->second->insert(s[r2]);
                po1->second->insert(r2);
                elemharsh[r2] = elemharsh[r1];
                posharsh[r2]  = posharsh[r1];
            }
            else if (po2 != posharsh.end()) {
                el2->second->insert(s[r1]);
                po2->second->insert(r1);
                elemharsh[r1] = elemharsh[r2];
                posharsh[r1]  = posharsh[r2];
            }
            else {
                elem.emplace_back(multiset<char>{ s[r1], s[r2] });
                pos.emplace_back(set<string::size_type>{ (size_t)r1, (size_t)r2 });
                elemharsh[r2] = elemharsh[r1] = --elem.end();
                posharsh[r2] = posharsh[r1] = --pos.end();
            }
        }
        auto elemit = elem.begin();
        auto posit  = pos.begin();
        for (; elemit != elem.end(); ++elemit, ++posit) {
            auto e = elemit->begin();
            auto p = posit->begin();
            for (; e != elemit->end(); ++e, ++p) s[*p] = *e;
        }
        return s;
    }
};
// @lc code=end
