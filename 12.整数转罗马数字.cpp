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
        vector<int> vals={1000,900,500,400,100,90,50,40,10,9,5,4,1};
        for(int v : vals){
            while(num >= v){
                res += mp[v];
                num -= v;
            }
        }
        return res;
    }
};
