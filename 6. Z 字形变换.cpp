我的想法：数学通项
#include<string>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows == 1) return s;
        string ans;
        int n = s.size();
        int cycle = 2 * numRows - 2;

        // 遍历每一行 i
        for(int i = 0; i < numRows; i++)
        {
            //k：周期编号
            for(int k = 0; k*cycle < n; k++)
            {
                //第一个字符
                int pos1 = k * cycle + i;
                if(pos1 < n)
                {
                    ans.push_back(s[pos1]);
                }
                
                //首行、末行，每个周期只有1个字符，跳过第二个
                if(i == 0 || i == numRows - 1)
                    continue;

                //中间行的第二个字符，用下一个周期减去i求出下标
                int pos2 = (k+1)*cycle - i;
                if(pos2 < n)
                {
                    ans.push_back(s[pos2]);
                }
            }
        }
        return ans;
    }
};


另：转化：以一个数组为周期，实现二维跳跃   
            *     *
从Z字型变成：|   |   |   |
            |   |   |   |
              *       * 
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        // 只有1行，Z字不存在，直接返回
        if(numRows == 1) return s;

        vector<string> rows(numRows); // numRows行，每行是一个string
        int curRow = 0;   // 当前正在填的行号
        bool down = false;// false向上，true向下

        for(char ch : s)
        {
            rows[curRow].push_back(ch); //字符放到当前行
            //到达上边界0，或者到达下边界numRows‑1，翻转方向
            if(curRow == 0 || curRow == numRows - 1)
            {
                down = !down;
            }
            //根据方向移动行号
            curRow += down ? 1 : -1;
        }

        //把所有行拼接成答案
        string ans;
        for(string &str : rows)
        {
            ans += str;
        }
        return ans;
    }
};












