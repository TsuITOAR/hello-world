/*
 * @lc app=leetcode.cn id=123 lang=cpp
 *
 * [123] 买卖股票的最佳时机 III
 */
#include <map>
#include <set>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    int maxProfit(vector<int>& prices) {
        int  k = 2;
        date start;
        for (date i = 0; i < prices.size(); ++i) {
            auto r = prices[i];
            if (r == prices.front())
                continue;
            else if (r > prices.front()) {
                valleys.insert(0);
                peaks.insert(1);
            }
            else if (r < prices.front()) {
                peaks.insert(0);
                valleys.insert(1);
            }
            fprices.assign({ prices[0], prices[i] });
            start = i;
            break;
        }
        for (date i = start, j = i + 1; i < prices.size(); i = j, j = i + 1) {
            if (*peaks.rbegin() == (fprices.size() - 1)) {
                while (j < prices.size() && prices[j] <= prices[j - 1]) ++j;
                valleys.insert(fprices.size());
            }

            else if (*valleys.rbegin() == (fprices.size() - 1)) {
                while (j < prices.size() && prices[j] >= prices[j - 1]) ++j;
                peaks.insert(fprices.size());
            }
            fprices.push_back(prices[j - 1]);
        }
        int fk = k;
        if (fprices.size() >= 2 && *peaks.rbegin() - *valleys.begin() > 0) {
            fk = fmin((*peaks.rbegin() - *valleys.begin() + 1) / 2, k);
        }
        else
            return 0;
        for (auto buy = *valleys.begin(); buy < fprices.size(); buy += 2) {
            auto nextsellday = buy + 1;

            auto lastbuyday(buy);
            auto lowestbuyday1(buy);

            bool  initial1 = 1;
            opera lasttrade1;
            for (auto sell(nextsellday); sell < fprices.size(); sell += 2) {
                auto trade = make_pair(buy, sell);
                if (initial1) {
                    maxRev[trade] = fprices[sell] - fprices[lowestbuyday1];
                    initial1      = 0;
                }
                else {
                    lastbuyday += 2;
                    lowestbuyday1 = fprices[lowestbuyday1] < fprices[lastbuyday] ? lowestbuyday1 : lastbuyday;
                    if (fprices[sell] - fprices[lowestbuyday1] > maxRev[lasttrade1])
                        maxRev[trade] = fprices[sell] - fprices[lowestbuyday1];
                    else
                        maxRev[trade] = maxRev[lasttrade1];
                }
                lasttrade1 = trade;
            }
        }
        int ret = 0;

        auto it = valleys.begin();
        for (auto sl = peaks.find(*it + 1); sl != peaks.end(); ++sl) {
            auto tem = 0;
            if (*sl > *it) tem += maxRev[make_pair(*it, *sl)];
            if (*sl + 1 < *peaks.rbegin()) tem += maxRev[make_pair(*sl + 1, *peaks.rbegin())];
            ret = fmax(ret, tem);
        }

        return ret;
    }

  private:
    typedef vector<int>      para;
    typedef para::size_type  date;
    typedef pair<date, date> opera;

    para            fprices;
    set<date>       peaks, valleys;
    set<date>       operas;
    map<opera, int> maxRev;
};
// @lc code=end
