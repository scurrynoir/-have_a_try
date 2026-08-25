我的想法：vector拆
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
    bool dfs(string &s, string &p, int j, vector<char> cur){
        //模式串走完，对比cur和s
        if(j == p.size()){
            if(cur.size() != s.size()) return false;
            for(int k=0;k<s.size();k++){
                if(cur[k] != s[k]) return false;
            }
            return true;
        }

        bool nextStar = (j+1 < p.size() && p[j+1] == '*');
        if(nextStar){
            char ch = p[j];
            //分支1：x*匹配0次，跳过x*
            if(dfs(s,p,j+2, cur)) return true;

            //分支2：匹配一次ch，继续可以再匹配（j不变）
            cur.push_back(ch);
            //剪枝：cur长度超过s就不要再往下走
            if(cur.size() <= s.size()){
                if(dfs(s,p,j, cur)) return true;
            }
            return false;
        }else{
            //普通字符 或者 .
            if(p[j] == '.'){
                //.必须匹配当前s对应位置的真实字符！不能随便塞'A'
                //这里关键：cur长度不能超过s
                if(cur.size() >= s.size()) return false;
                cur.push_back(s[cur.size()]); 
            }else{
                cur.push_back(p[j]);
            }
            return dfs(s,p,j+1, cur);
        }
    }

    bool isMatch(string s, string p) {
        vector<char> tmp;
        return dfs(s,p,0,tmp);
    }
};

另：暴力：递归回溯（不带 DP，纯暴力）
class Solution {
public:
    bool dfs(string &s, string &p, int i, int j)
    {
        // 全部走完
        if(i == s.size() && j == p.size())
            return true;
        // p走完了，s还有剩余，失败
        if(j == p.size())
            return false;

        bool nextIsStar = (j+1 < p.size() && p[j+1] == '*');

        if(nextIsStar)
        {
            // 选项1：x*匹配0次，直接跳过这一组 x*
            bool op0 = dfs(s,p,i, j+2);

            // 选项2：当前字符匹配，x*匹配一次，s前进
            bool op1 = false;
            if(i < s.size() && (s[i]==p[j] || p[j]=='.'))
            {
                op1 = dfs(s,p,i+1, j);
            }
            return op0 || op1;
        }
        else
        {
            //没有*，普通匹配
            if(i < s.size() && (s[i]==p[j] || p[j]=='.'))
            {
                return dfs(s,p,i+1,j+1);
            }
            return false;
        }
    }

    bool isMatch(string s, string p) {
        return dfs(s,p,0,0);
    }
};

标答：动态规划
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int ns = s.size();
        int np = p.size();
        vector<vector<bool>> dp(ns+1, vector<bool>(np+1, false));
        dp[0][0] = true;

        //初始化：处理p开头有 a* b*这种，可以匹配空s
        for(int j = 2; j <= np; j++){
            if(p[j-1] == '*'){
                dp[0][j] = dp[0][j-2];
            }
        }

        for(int i = 1; i <= ns; i++)
        {
            for(int j = 1; j <= np; j++)
            {
                if(p[j-1] != '*')
                {
                    //普通字符 or '.'
                    dp[i][j] = dp[i-1][j-1] && (s[i-1]==p[j-1] || p[j-1]=='.');
                }
                else
                {
                    // p[j-1]是 *
                    // 情况1：x*取0次；情况2：x*取多次
                    dp[i][j] = dp[i][j-2];
                    if(s[i-1]==p[j-2] || p[j-2]=='.')
                    {
                        dp[i][j] = dp[i][j] || dp[i-1][j];
                    }
                }
            }
        }
        return dp[ns][np];
    }
};



