我的想法：暴力双指针
#include<string>
#include<vector>
#include<unordered_set>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int maxLen = 0;  
        for(int i = 0; i < n; i++)       //枚举起点i
        {
            unordered_set<char> st;      // `unordered_set` 保存当前窗口已经出现过的字符。
            for(int j = i; j < n; j++)   //j向右扩展
            {
                if(st.count(s[j]))       //字符已经存在，重复，直接break
                {
                    break;
                }
                st.insert(s[j]);
                maxLen = max(maxLen, j - i + 1);
            }
        }
        return maxLen;
    }
};
