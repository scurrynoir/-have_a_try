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
