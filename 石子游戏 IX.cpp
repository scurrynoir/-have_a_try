暴力：
#include <iostream>
#include <vector>
using namespace std;

// dfs：当前模sumMod，剩余cnt0,cnt1,cnt2；isAlice是否轮到Alice
bool dfs(int sumMod, int cnt0, int cnt1, int cnt2, bool isAlice)
{
    // =========尝试拿 type0 (val%3==0) =========
    if(cnt0 > 0)
    {
        int newMod = (sumMod + 0) %3;
        //拿完之后模等于0 → 当前玩家输掉，这个选择不能走
        if(newMod == 0)
        {
            //不能选这个，试下一个
        }
        else
        {
            //选0，轮到对手；对手返回false代表对手必败 → 当前我方必胜
            if(!dfs(newMod, cnt0-1, cnt1, cnt2, !isAlice))
            {
                return true;
            }
        }
    }

    // =========尝试拿 type1 (val%3==1) =========
    if(cnt1 > 0)
    {
        int newMod = (sumMod + 1) %3;
        if(newMod == 0)
        {
            //拿1直接输，跳过
        }
        else
        {
            if(!dfs(newMod, cnt0, cnt1-1, cnt2, !isAlice))
            {
                return true;
            }
        }
    }

    // =========尝试拿 type2 (val%3==2) =========
    if(cnt2 > 0)
    {
        int newMod = (sumMod + 2) %3;
        if(newMod ==0)
        {
            //拿2直接输，跳过
        }
        else
        {
            if(!dfs(newMod, cnt0, cnt1, cnt2-1, !isAlice))
            {
                return true;
            }
        }
    }

    //所有可选走法全部试完，没有任何一种能让对手必败 → 当前玩家必败
    return false;
}

class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt0=0,cnt1=0,cnt2=0;
        for(int v : stones)
        {
            if(v%3==0) cnt0++;
            else if(v%3==1) cnt1++;
            else cnt2++;
        }
        //初始总和是0，轮到Alice
        return dfs(0,cnt0,cnt1,cnt2,true);
    }
};

int main()
{
    Solution sol;
    vector<int> s1={1,2};
    cout<<(sol.stoneGameIX(s1)?"true":"false")<<endl; //true

    vector<int> s2={3,3,3};
    cout<<(sol.stoneGameIX(s2)?"true":"false")<<endl; //false

    vector<int> s3={1,1,1,2};
    cout<<(sol.stoneGameIX(s3)?"true":"false")<<endl; //true
    return 0;
}
当前复杂度:O(3^(cnt0+cnt1+cnt2))



正解：
class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt0 = 0, cnt1 = 0, cnt2 = 0;
        for (int val: stones) {
            if (int type = val % 3; type == 0) {
                ++cnt0;
            }
            else if (type == 1) {
                ++cnt1;
            }
            else {
                ++cnt2;
            }
        }
        if (cnt0 % 2 == 0) {
            return cnt1 >= 1 && cnt2 >= 1;
        }
        return cnt1 - cnt2 > 2 || cnt2 - cnt1 > 2;
    }
};
时间复杂度：O(n)，其中 n 是数组 stones 的长度。
空间复杂度：O(1)。

作者：力扣官方题解
链接：https://leetcode.cn/problems/stone-game-ix/solutions/1220220/shi-zi-you-xi-ix-by-leetcode-solution-kk5f/


  
