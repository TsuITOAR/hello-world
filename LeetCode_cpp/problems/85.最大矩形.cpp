/*
 * @lc app=leetcode.cn id=85 lang=cpp
 *
 * [85] 最大矩形
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
// @lc code=start
#define makerange(X1, X2, Y1, Y2) \
    {                             \
        { X1, X2 }, { Y1, Y2 }    \
    }

#define rangeSize(a) ((a).first.second - (a).first.first + 1) * ((a).second.second - (a).second.first + 1)
class Solution
{
  public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix.front().empty()) return 0;
        curmax = 0;
        maxinArea(0, matrix.front().size() - 1, 0, matrix.size() - 1, matrix);
        return curmax;
    }

  private:
    typedef vector<vector<char>>                 area;
    typedef typename area::size_type             Y;
    typedef typename area::value_type::size_type X;
    typedef pair<pair<X, X>, pair<Y, Y>>         range;

    int curmax;

    void maxinArea(const X& Xbeg, const X& Xend, const Y& Ybeg, const Y& Yend, const area& matrix) {
        vector<pair<int, int>> d{ { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };

        for (const auto r : d) {
            auto dx = r.first;
            auto dy = r.second;
            for (auto y = (Ybeg + Yend) / 2; y >= Ybeg && y <= Yend; y += dy)
                for (auto x = (Xbeg + Xend) / 2; x >= Xbeg && x <= Xend; x += dx) {
                    if (matrix[y][x] == '0') {
                        vector<range> ranges;
                        if (y != Ybeg) {
                            if (x != Xbeg) ranges.push_back(makerange(Xbeg, x - 1, Ybeg, y - 1));
                            if (x != Xend) ranges.push_back(makerange(x + 1, Xend, Ybeg, y - 1));
                        }
                        if (y != Yend) {
                            if (x != Xbeg) ranges.push_back(makerange(Xbeg, x - 1, y + 1, Yend));
                            if (x != Xend) ranges.push_back(makerange(x + 1, Xend, y + 1, Yend));
                        }
                        maxonlineY(x, makerange(Xbeg, Xend, Ybeg, Yend), matrix);
                        maxonlineX(y, makerange(Xbeg, Xend, Ybeg, Yend), matrix);
                        for (auto t = ranges.rbegin(); t != ranges.rend(); ++t) {
                            if (rangeSize(*t) > curmax) maxinArea(*t, matrix);
                        }
                        return;
                    }
                }
        }
        curmax = fmax(curmax, (Xend - Xbeg + 1) * (Yend - Ybeg + 1));
        return;
    }
    void maxonlineY(const X& x, const range& r, const area& matrix) {
        map<Y, int> left, right;
        for (auto y = r.second.first; y <= r.second.second; ++y) {
            if (matrix[y][x] == '0') continue;
            for (auto p = x - 1; p >= r.first.first && p < x && matrix[y][p] == '1'; --p) ++left[y];
            for (auto q = x + 1; q <= r.first.second && q > x && matrix[y][q] == '1'; ++q) ++right[y];
        }
        auto start = r.second.first;
        while (start <= r.second.second && matrix[start][x] == '0') ++start;

        int maxSize = 0;
        while (start <= r.second.second) {
            auto end = start;
            while (end <= r.second.second && matrix[end][x] == '1') ++end;
            map<pair<Y, Y>, int> maxleft, maxright;
            for (auto i = start; i < end; ++i) {
                maxleft[{ i, i }]  = left[i];
                maxright[{ i, i }] = right[i];

                maxSize = fmax(maxSize, maxleft[{ i, i }] + maxright[{ i, i }] + 1);
                for (auto j = i + 1; j < end; ++j) {
                    maxleft[{ i, j }]  = fmin(maxleft[{ i, j - 1 }], left[j]);
                    maxright[{ i, j }] = fmin(maxright[{ i, j - 1 }], right[j]);

                    maxSize = fmax(maxSize, (maxleft[{ i, j }] + maxright[{ i, j }] + 1) * (j - i + 1));
                }
            }
            start = end;
            while (start <= r.second.second && matrix[start][x] == '0') ++start;
        }
        curmax = fmax(curmax, maxSize);
    }
    void maxonlineX(const Y& y, const range& r, const area& matrix) {
        map<X, int> down, up;
        for (auto x = r.first.first; x <= r.first.second; ++x) {
            if (matrix[y][x] == '0') continue;
            for (auto p = y - 1; p >= r.second.first && p < y && matrix[p][x] == '1'; --p) ++down[x];
            for (auto q = y + 1; q <= r.second.second && q > y && matrix[q][x] == '1'; ++q) ++up[x];
        }
        auto start = r.first.first;
        while (start <= r.first.second && matrix[y][start] == '0') ++start;

        int maxSize = 0;
        while (start <= r.first.second) {
            auto end = start;
            while (end <= r.first.second && matrix[y][end] == '1') ++end;
            map<pair<X, X>, int> maxdown, maxup;
            for (auto i = start; i < end; ++i) {
                maxdown[{ i, i }] = down[i];
                maxup[{ i, i }]   = up[i];

                maxSize = fmax(maxSize, maxdown[{ i, i }] + maxup[{ i, i }] + 1);
                for (auto j = i + 1; j < end; ++j) {
                    maxdown[{ i, j }] = fmin(maxdown[{ i, j - 1 }], down[j]);
                    maxup[{ i, j }]   = fmin(maxup[{ i, j - 1 }], up[j]);

                    maxSize = fmax(maxSize, (maxdown[{ i, j }] + maxup[{ i, j }] + 1) * (j - i + 1));
                }
            }
            start = end;
            while (start <= r.first.second && matrix[y][start] == '0') ++start;
        }
        curmax = fmax(curmax, maxSize);
    }

    void maxinArea(const range& r, const area& matrix) {
        maxinArea(r.first.first, r.first.second, r.second.first, r.second.second, matrix);
    }
};
// @lc code=end
