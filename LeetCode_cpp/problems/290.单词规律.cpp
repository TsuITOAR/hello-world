/*
 * @lc app=leetcode.cn id=290 lang=cpp
 *
 * [290] 单词规律
 */
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    bool wordPattern(string pattern, string s) {
        unordered_map<string, char> link;
        unordered_map<char, string> rlink;
        string::size_type beg = 0, end;
        string::size_type pos = 0;
        while (end != string::npos && pos < pattern.size()) {
            end             = s.find(' ', beg);
            const auto& str = s.substr(beg, end - beg);
            const auto& sym = pattern[pos];
            if (link.find(str) == link.end() && rlink.find(sym) == rlink.end()) {
                link[str]  = sym;
                rlink[sym] = str;
            }
            else if (link.find(str) != link.end() && rlink.find(sym) != rlink.end()) {
                if (link[str] != sym || rlink[sym] != str) return 0;
            }
            else
                return 0;
            ++pos;
            beg = end + 1;
        }
        return end == string::npos && pos == pattern.size();
    }
};
// @lc code=end
