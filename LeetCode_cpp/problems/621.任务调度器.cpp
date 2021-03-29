/*
 * @lc app=leetcode.cn id=621 lang=cpp
 *
 * [621] 任务调度器
 */
#include <iostream>
#include <map>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    int leastInterval(vector<char>& tasks, int n) {
        map<char, int>      numOfTask;
        multimap<int, char> timeOfCD;
        for (const auto& r : tasks) {
            ++numOfTask[r];
            if (numOfTask[r] == 1)
                timeOfCD.insert(make_pair(0, r));
        }
        int                     time = 0;
        vector<char>::size_type i    = 0;
        while (i < tasks.size()) {
            vector<multimap<int, char>::iterator> runableTask;
            for (auto it = timeOfCD.begin(); it != timeOfCD.upper_bound(time); ++it)
                runableTask.push_back(it);

            auto itRange = make_pair(runableTask.begin(), runableTask.end());
            if (itRange.first != itRange.second) {
                auto taskToRun = itRange.first;
                for (auto it = itRange.first; it != itRange.second; ++it) {
                    if (numOfTask[(**it).second] > numOfTask[(**taskToRun).second])
                        taskToRun = it;
                }
                --numOfTask[(**taskToRun).second];
                ++i;
                auto temp = make_pair((**taskToRun).first + n + 1, (**taskToRun).second);
                timeOfCD.erase(*taskToRun);
                if (numOfTask[temp.second]) timeOfCD.insert(temp);
            }
            ++time;
        }
        return time;
    }
};
// @lc code=end
