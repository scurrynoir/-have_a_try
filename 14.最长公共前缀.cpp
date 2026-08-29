思路一：横向
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
        // 初始公共前缀为第一个字符串
        string pre = strs[0];

        //遍历剩下所有字符串
        for(int i = 1; i < strs.size(); i++)
        {
            // pre不是当前字符串的前缀，就缩短末尾一个字符
            while(strs[i].find(pre) != 0)
            {
                pre = pre.substr(0, pre.size() - 1);
                if(pre.empty()) return "";
            }
        }
        return pre;
    }
};



思路二：纵向
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
        // 遍历第一个字符串每一列（每一个位置）
        for(int col = 0; col < strs[0].size(); col++)
        {
            char c = strs[0][col];
            // 拿这个字符和所有其他字符串同一列对比
            for(int row = 1; row < strs.size(); row++)
            {
                // 1.别的字符串已经到头  2.字符不相等 →直接返回前面已经匹配的前缀
                if(col == strs[row].size() || strs[row][col] != c)
                {
                    return strs[0].substr(0, col);
                }
            }
        }
        return strs[0];
    }
};

