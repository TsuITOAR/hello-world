/*
 * @lc app=leetcode.cn id=188 lang=cpp
 *
 * [188] 买卖股票的最佳时机 IV
 */
#include <map>
#include <set>
#include <vector>

using namespace std;
// @lc code=start
class Solution
{
  public:
    int maxProfit(int k, vector<int>& prices) {
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
                    maxRev[trade]    = fprices[sell] - fprices[lowestbuyday1];
                    maxRevBuy[trade] = trade;
                    initial1         = 0;
                }
                else {
                    lastbuyday += 2;
                    lowestbuyday1 = fprices[lowestbuyday1] < fprices[lastbuyday] ? lowestbuyday1 : lastbuyday;
                    if (fprices[sell] - fprices[lowestbuyday1] > maxRev[lasttrade1]) {
                        maxRev[trade]    = fprices[sell] - fprices[lowestbuyday1];
                        maxRevBuy[trade] = make_pair(lowestbuyday1, sell);
                    }
                    else {
                        maxRev[trade]    = maxRev[lasttrade1];
                        maxRevBuy[trade] = maxRevBuy[lasttrade1];
                    }
                }
                lasttrade1 = trade;
            }
            auto lastsellday = buy - 1;

            auto nextbuyday(buy);
            auto lowestbuyday2(buy);

            bool  initial2 = 1;
            opera lasttrade2;
            for (auto sell(lastsellday); sell >= 0 && sell < fprices.size(); sell -= 2) {
                auto trade = make_pair(sell, buy);
                if (initial2) {
                    maxRev[trade]    = fprices[sell] - fprices[lowestbuyday2];
                    maxRevBuy[trade] = trade;
                    initial2         = 0;
                }
                else {
                    nextbuyday -= 2;
                    lowestbuyday2 = fprices[lowestbuyday2] < fprices[nextbuyday] ? lowestbuyday2 : nextbuyday;
                    if (fprices[sell] - fprices[lowestbuyday2] > maxRev[lasttrade2]) {
                        maxRev[trade]    = fprices[sell] - fprices[lowestbuyday2];
                        maxRevBuy[trade] = make_pair(lowestbuyday2, sell);
                    }
                    else {
                        maxRev[trade]    = maxRev[lasttrade2];
                        maxRevBuy[trade] = maxRevBuy[lasttrade2];
                    }
                }
                lasttrade2 = trade;
            }
        }
        int ret = 0;

        while (fk > 0) {
            ret += smartestBuy();
            --fk;
        }
        return ret;
    }

  private:
    typedef vector<int>      para;
    typedef para::size_type  date;
    typedef pair<date, date> opera;

    para              fprices;
    set<date>         peaks, valleys;
    set<date>         operas;
    map<opera, int>   maxRev;
    map<opera, opera> maxRevBuy;

    int smartestBuy() {
        auto begin = *valleys.begin();
        int  rev   = 0;

        decltype(begin) end;

        int   tem;
        opera trade;

        opera smartBuy;

        for (auto it = operas.begin(); it != operas.end(); ++it) {
            end = *it - 1;
            if (begin < end) {
                trade = make_pair(begin, end);
                tem   = maxRev[trade];
                if (tem > rev) {
                    rev      = tem;
                    smartBuy = maxRevBuy[trade];
                }
            }
            begin = *it + 1;
        }

        end = *peaks.rbegin();
        if (begin < end) {
            trade = make_pair(begin, end);
            tem   = maxRev[trade];
            if (tem > rev) {
                rev      = tem;
                smartBuy = maxRevBuy[trade];
            }
        }
        if (rev != 0) {
            operas.insert(smartBuy.first);
            operas.insert(smartBuy.second);
        }
        return rev;
    }
};
// @lc code=end
