我的垃圾思路：两头往中间缩
class Solution {
public:
    string longestPalindrome(string s) {
        int n=s.length();
        int i=0;int j=n-1;int max=0;int p=i;int q=j;
        while (p<q){
            while (i<j && s[i]==s[j]) {i++;j--;}
            int m=j-i;
            if (m>max) max=m;
            int p=i;int q=j;
        }
        return max;        <——大错：函数返回是string，我返回int数字
    }
};


双指针 `i,j` 从两头往中间缩的写法**不能解决这道题**。
这种两头对撞只适合判断**整个字符串是不是回文**，不能找中间某一段最长回文子串。
例：`"babad"`，整体不是回文，但中间 `"bab"`、`"aba"`是回文。
    
暴力解法：
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if(n <= 1) return s;
        int maxLen = 1;
        int start = 0;

        //枚举起点
        for(int i = 0; i < n; i++)
        {
            //枚举终点
            for(int j = i; j < n; j++)
            {
                //判断 s[i]~s[j] 是否回文
                int l = i, r = j;
                bool ok = true;
                while(l < r)
                {
                    if(s[l] != s[r]){
                        ok = false;
                        break;
                    }
                    l++; r--;
                }
                if(ok)
                {
                    int len = j - i + 1;
                    if(len > maxLen)
                    {
                        maxLen = len;
                        start = i;
                    }
                }
            }
        }
        return s.substr(start, maxLen);
    }
};



另：中心扩散
#include<string>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        if(s.size() <= 1) return s;
        int start = 0;
        int maxLen = 1;

        // 以left,right为中心向外扩散
        auto expand = [&](int left, int right){
            while(left >=0 && right < s.size() && s[left]==s[right])
            {
                left--;
                right++;
            }
            // 退出循环时，left、right已经多走一步
            int len = right - left - 1;
            if(len > maxLen)
            {
                maxLen = len;
                start = left + 1;
            }
        };

        for(int i = 0; i < s.size(); i++)
        {
            expand(i,i);      //奇数回文中心
            expand(i,i+1);    //偶数回文中心
        }
        return s.substr(start, maxLen);
    }
};
时间复杂度 (O(n^2))，空间 (O(1))






class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();              // 获取字符串总长度n
        if(n <= 1) return s;           // 字符串长度0或者1，本身就是回文，直接返回
        int maxLen = 1;                // 记录最长回文子串的长度，初始至少为1（单个字符）
        int start = 0;                 // 记录最长回文子串的起始下标
        
        // 创建n*n二维bool dp数组，全部初始化为false
        // dp[i][j] 含义：字符串下标[i, j] 的子串是否是回文，true是回文，false不是
        vector<vector<bool>> dp(n,vector<bool>(n,false));

        //单个字符一定是回文
        for(int i=0;i<n;i++) 
        {
            dp[i][i]=true;   // i到i，就一个字符，一定回文
        }

        //len是子串的长度，从长度2开始，一直到整个字符串长度n
        for(int len = 2; len <= n; len++)
        {
            // i：子串的起点下标
            // i + len -1 是子串终点j，j不能超过n‑1，所以循环条件 i + len -1 < n
            for(int i = 0; i + len -1 < n; i++)
            {
                int j = i + len -1;   // j：子串的终点下标，[i,j] 一共len个字符

                if(s[i]==s[j])        // 如果子串的第一个字符 和最后一个字符相等
                {
                    if(len == 2){
                        //子串长度等于2，两个字符相等，直接就是回文，例如 "aa"
                        dp[i][j]=true;
                    }else{
                        //长度大于2：两头字符相等，还要看中间[i+1 , j‑1]是不是回文
                        dp[i][j] = dp[i+1][j-1];
                    }

                    // 如果当前[i,j]是回文，并且长度比记录的maxLen更大
                    if(dp[i][j] && len>maxLen)
                    {
                        maxLen = len;  // 更新最长回文的长度
                        start = i;     // 更新最长回文的起始下标
                    }
                }
                // 如果 s[i]!=s[j]，dp[i][j]保持false，不用处理
            }
        }
        // 从start下标开始，截取maxLen个字符，返回这个子串
        return s.substr(start,maxLen);
    }
};


