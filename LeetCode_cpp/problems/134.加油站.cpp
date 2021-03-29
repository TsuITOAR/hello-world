/*
 * @lc app=leetcode.cn id=134 lang=cpp
 *
 * [134] 加油站
 */
#include <iostream>
#include <vector>
using namespace std;
// @lc code=start
/*
* 在vector中擦除每个合并的节点
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        vector<int>::size_type i=0,j=0;
        int tem;
        for(i=0;i<gas.size();++i) {
            tem=gas[i]-cost[i];
            if(rev.empty()||tem*rev.back()<0) {rev.push_back(tem);rep.push_back(i);}
            else rev.back()+=tem;
        }
        if(rev.size()==1) return rev.front()>=0?rep.front():-1;
        i=0;
        while(i<rev.size()){
            if(rev[i]<0) {++i;continue;}
            j=after(i);
            while(rev[i]+rev[j]>=0){
                rev[i]+=rev[j];
                rev.erase(rev.begin()+j);
                rep.erase(rep.begin()+j);
                if(rep.size()==1) return rep.front();
                if(j==rev.size()) j=0;
            }
            if(j<i) return -1;
            i=j+1;
        }
        return -1;
    }
private:
    vector<long> rev;
    vector<int> rep;
    vector<int>::size_type after(vector<int>::size_type i){
        if(i>=rev.size()-1) return 0;
        else return i+1;
    }
};

*/

/*
* 记忆性选择
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        for(vector<int>::size_type i=0;i<gas.size();++i) rev.push_back(gas[i]-cost[i]);
        if(rev.size()==1) return rev.front()>=0?0:-1;
        last.assign(rev.size(),{-1,-1});
        int saving=0,end=0;
        vector<int>::size_type i=0,j=0;
        int s=0;
        do{
            if(rev[i]<0) 1;
            else{
                j=i;saving=rev[i];s=0;
                while(saving>=0){
                    if(last[j][0]!=-1&&last[j][0]!=j) {
                        saving+=last[j][1]-rev[j];
                        j=last[j][0];
                    }
                    else{
                        j=next(j);
                        saving+=rev[j];
                    }
                    if(j==i) return i;
                    if(j==0) s=1;
                }
                if(s==1) end=fmax(j,end);
                saving-=rev[j];
                j=before(j);
                last[i][0]=j;last[i][1]=saving;
            }
            i=before(i);
        }while(i>end);
        return -1;
    }
private:
    vector<int> rev;
    vector<int>::size_type next(vector<int>::size_type i){
        if(i==rev.size()-1) return 0;
        else return i+1;
    }
    vector<int>::size_type before(vector<int>::size_type i){
        if(i==0) return rev.size()-1;
        else return i-1;
    }
    vector<vector<int>> last;
};

*/

/*
* 单次遍历数组
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        for(vector<int>::size_type i=0;i<gas.size();++i) rev.push_back(gas[i]-cost[i]);
        if(rev.size()==1) return rev.front()>=0?0:-1;
        int saving=0;
        for(vector<int>::size_type i=0,j=0;i<rev.size();i=j+1){
            j=i;saving=rev[i];
            while(saving>=0){
                j=next(j);
                saving+=rev[j];
                if(j==i) return i;
            }
            if(j<i) return -1;
        }
        return -1;
    }
private:
    vector<int> rev;
    vector<int>::size_type next(vector<int>::size_type i){
        if(i==rev.size()-1) return 0;
        else return i+1;
    }
};
*/

// 环形链表结构模拟，删去每个合并的节点

class Solution
{
  public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        station* head = nullptr;
        int      k    = 0;
        for (int i = gas.size() - 1; i >= 0; --i) {
            head = new station(i, gas[i] - cost[i], head);
        }
        auto H   = head;
        long sum = 0;
        while (head->next != nullptr) {
            sum += head->rev;
            head = head->next;
        }
        sum += head->rev;
        if (sum < 0)
            return -1;
        head->next = H;
        int TIMES  = MAXTRY;
        while ((TIMES--) > 0) {
            if (H->rev >= 0) {
                while (H->rev + H->next->rev >= 0) {
                    H->rev += H->next->rev;
                    H->next = H->next->next;
                    if (H->next == H)
                        return H->id;
                }
                H = H->next->next;
            }
            else
                H = H->next;
        }
        return H->id;
    }

  private:
    static const int MAXTRY = 10000;
    struct station
    {
        station() = default;
        station(int a, int b, station* c) : id(a), rev(b), next(c) {}
        int      id;
        long     rev;
        station* next;
        void     print() {
            cout << "id\t=\t" << id << endl;
            cout << "rev\t=\t" << rev << endl;
        }
    };
};
// @lc code=end
