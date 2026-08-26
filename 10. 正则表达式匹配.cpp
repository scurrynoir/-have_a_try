我的想法：vector拆
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
    // s：原字符串；p：正则模式串
    // j：p当前处理到的下标
    // cur：vector<char>，当前递归分支生成出来的模式字符串
    bool dfs(string &s, string &p, int j, vector<char> cur){
        // ========= 递归终止条件：模式串全部处理完毕 =========
        if(j == p.size()){
            // 如果生成出来的cur长度和s不一样，直接不匹配
            if(cur.size() != s.size()) return false;
            // 逐个字符对比cur和s
            for(int k=0;k<s.size();k++){
                if(cur[k] != s[k]) return false;
            }
            // 全部字符相等 → 匹配成功
            return true;
        }

        // 判断：p下一个字符是不是 *
        // j+1不能越界，同时p[j+1]等于'*'
        bool nextStar = (j+1 < p.size() && p[j+1] == '*');

        if(nextStar){
            char ch = p[j];   // *前面的那个字符 x，也就是 x* 的x

            // --------分支1：x*匹配0次，完全不用这个字符，直接跳过x*这两个字符 j+2 --------
            if(dfs(s,p,j+2, cur)) return true;

            // --------分支2：x*匹配1次，把ch加入cur，j不变（还可以继续重复匹配这个x）--------
            cur.push_back(ch);

            // 剪枝：cur已经比s长了，继续push只会更长，没必要递归，防止无限递归
            if(cur.size() <= s.size()){
                // j不变！还停在x的位置，下一轮还可以继续选匹配多次
                if(dfs(s,p,j, cur)) return true;
            }

            // 0次分支、多次分支都走不通，返回false
            return false;
        }else{
            // ================= 没有*，普通字符 或者 . =================
            if(p[j] == '.'){
                // .代表任意一个字符，不能随便塞一个假字符
                // cur现在的长度，就是即将填充的位置，直接拿s对应位置真实字符放入cur
                if(cur.size() >= s.size()) return false; // s已经用完，还需要填字符，失败
                cur.push_back(s[cur.size()]); 
            }else{
                // 普通字符，直接把模式字符放进cur
                cur.push_back(p[j]);
            }
            // 当前位置处理完成，处理p下一个字符 j+1
            return dfs(s,p,j+1, cur);
        }
    }

    bool isMatch(string s, string p) {
        vector<char> tmp; // 初始是空vector，用来存递归生成的字符串
        return dfs(s,p,0,tmp); // 从p下标0开始递归
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



