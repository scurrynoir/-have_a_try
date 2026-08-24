#include <iostream>
#include <string>
#include <climits>
using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        int n = s.size();
        int i = 0;
        int sign = 1;   //符号，1正 -1负
        long long res = 0;

        //1.跳过前导空格
        while(i < n && s[i] == ' '){
            i++;
        }

        //2.处理正负号，只允许一个
        if(i < n && (s[i] == '+' || s[i] == '-')){
            if(s[i] == '-') sign = -1;
            i++;
        }

        //3.读取连续数字字符
        while(i < n && s[i] >= '0' && s[i] <= '9'){
            int digit = s[i] - '0'; //字符转数字
            res = res * 10 + digit;

            //提前判断溢出
            if(res * sign > INT_MAX) return INT_MAX;
            if(res * sign < INT_MIN) return INT_MIN;

            i++;
        }

        res = res * sign;
        return (int)res;
    }
};

虽然`res`是 long long 可以跑，但力扣标准写法更推荐**先不乘 sign，拿正数 res 做边界判断**，避免迷惑。

于是：
#include <string>
#include <climits>
using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        int n = s.size();
        int i = 0;
        int sign = 1;
        long long res = 0;

        // 跳过空格
        while(i < n && s[i] == ' ') i++;

        // 符号
        if(i < n && (s[i] == '+' || s[i] == '-')){
            if(s[i] == '-') sign = -1;
            i++;
        }

        // 读取数字，重点：res = res*10+digit 不能丢
        while(i < n && s[i] >= '0' && s[i] <= '9'){
            int digit = s[i] - '0';
            res = res * 10 + digit;

            // 正数溢出判断
            if(res > INT_MAX)
            {
                return sign == 1 ? INT_MAX : INT_MIN;
            }
            i++;
        }
        res = res * sign;
        return (int)res;
    }
};

