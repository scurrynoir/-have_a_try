我的想法：用vector存下之后倒着加
#include<vector>
#include<iostream>
#include<climits>
using namespace std;

class Solution {
public:
    int reverse(int x) {
        vector<int> arr;
        bool neg = false;
        if(x < 0){
            neg = true;
        }
        while(x != 0){
            int a = abs(x%10); //取绝对值，数组只存正数
            arr.push_back(a);
            x /= 10;
        }
        long long ans = 0;
        for(int num : arr){
            ans = ans*10 + num;
        }
        if(neg) ans = -ans; //neg真正生效
        if(ans>INT_MAX || ans<INT_MIN) return 0;
        return (int)ans;
    }

        
};
