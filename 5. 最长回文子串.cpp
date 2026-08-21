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

