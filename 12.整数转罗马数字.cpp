我的想法：哈希表
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        // key:数值，value:罗马字符串
        unordered_map<int,string> mp = {
            {1000,"M"},{900,"CM"},{500,"D"},{400,"CD"},
            {100,"C"},{90,"XC"},{50,"L"},{40,"XL"},
            {10,"X"},{9,"IX"},{5,"V"},{4,"IV"},{1,"I"}
        };
        string res;
              
        //unordered_map无序！不能直接遍历，必须手动按从大到小顺序写一遍key
        vector<int> vals={1000,900,500,400,100,90,50,40,10,9,5,4,1};  //必须额外开一个数组存 key 的先后顺序
        for(int v : vals){
            while(num >= v){
                res += mp[v];
                num -= v;
            }
        }
        return res;
    }
};


另算法思路（贪心）：
优先用最大的罗马符号去消耗 num

#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    string intToRoman(int num) {
        
        // pair<数值，罗马符号>，手动按从大到小排好
        vector<pair<int, string>> table = {
            {1000,"M"},{900,"CM"},{500,"D"},{400,"CD"},
            {100,"C"},{90,"XC"},{50,"L"},{40,"XL"},
            {10,"X"},{9,"IX"},{5,"V"},{4,"IV"},{1,"I"}
        };
        string ans;
        for(auto &p : table)
        {
            int val = p.first;
            string sym = p.second;
            
            // 当前数字还比这个符号代表的值大，就不断拼接
            while(num >= val)
            {
                ans += sym;
                num -= val;
            }
        }
        return ans;
    }
};
