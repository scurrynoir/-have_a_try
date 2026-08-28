我的想法：哈希表
#include <unordered_map>
#include <string>
using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> mp{
            {'I',1},
            {'V',5},
            {'X',10},
            {'L',50},
            {'C',100},
            {'D',500},
            {'M',1000}
        };
        int ans = 0;
        int n = s.size();
        for(int i = 0; i < n; i++){
            // 当前比右边小 → 减
            if(i+1 < n && mp[s[i]] < mp[s[i+1]]){
                ans -= mp[s[i]];
            }else{
                ans += mp[s[i]];
            }
        }
        return ans;
    }
};

