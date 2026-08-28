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

另：把 6 种减法组合直接替换成普通字符，再全部求和
class Solution {
public:
    int romanToInt(string s) {
        // 思路：把6个减法特殊组合，替换成等价普通罗马串，之后直接全部累加
        // IV=4 → IIII；IX=9→VIIII；XL=40→XXXX；XC=90→LXXXX；CD=400→CCCC；CM=900→DCCCC

        // find("IV")：查找子串IV，找到返回下标；找不到返回 string::npos
        while(s.find("IV")!=string::npos)  //当没找到子串时
        {
            // replace(起始位置,替换长度,新字符串)
            // 找到IV，从该位置开始，替换2个字符，换成IIII
            s.replace(s.find("IV"),2,"IIII");
        }

        // 处理 IX = 9
        while(s.find("IX")!=string::npos)
        {
            s.replace(s.find("IX"),2,"VIIII");
        }

        // 处理 XL = 40
        while(s.find("XL")!=string::npos)
        {
            s.replace(s.find("XL"),2,"XXXX");
        }

        // 处理 XC = 90
        while(s.find("XC")!=string::npos)
        {
            s.replace(s.find("XC"),2,"LXXXX");
        }

        // 处理 CD = 400
        while(s.find("CD")!=string::npos)
        {
            s.replace(s.find("CD"),2,"CCCC");
        }

        // 处理 CM = 900
        while(s.find("CM")!=string::npos)
        {
            s.replace(s.find("CM"),2,"DCCCC");
        }

        // 建立字符→数值映射，利用ASCII数组，下标是char
        int val[256]={0};
        val['I']=1;
        val['V']=5;
        val['X']=10;
        val['L']=50;
        val['C']=100;
        val['D']=500;
        val['M']=1000;

        int ans=0;
        //遍历替换完成后的字符串，全部相加
        for(char ch:s)
        {
            ans += val[ch];
        }
        return ans;
    }
};


另：递归思路
class Solution {
public:
    int val[256]={0};
    int dfs(string &s,int i){
        if(i>=s.size()) return 0;
        // 判断是不是减法二元组合
        if(i+1<s.size()){
            string sub = s.substr(i,2);   //substr (起点，取多少个)；缺省长度就截到末尾。
            if(sub=="IV") return 4 + dfs(s,i+2);
            if(sub=="IX") return 9 + dfs(s,i+2);
            if(sub=="XL") return 40 + dfs(s,i+2);
            if(sub=="XC") return 90 + dfs(s,i+2);
            if(sub=="CD") return 400 + dfs(s,i+2);
            if(sub=="CM") return 900 + dfs(s,i+2);
        }
        //普通单个字符
        return val[s[i]] + dfs(s,i+1);
    }
    int romanToInt(string s) {
        val['I']=1;val['V']=5;val['X']=10;val['L']=50;
        val['C']=100;val['D']=500;val['M']=1000;
        return dfs(s,0);
    }
};


