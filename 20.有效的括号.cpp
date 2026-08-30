我的思路：栈
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(char c : s)
        {
            //左括号入栈
            if(c == '(' || c == '{' || c == '[')
            {
                st.push(c);
            }
            else
            {
                //右括号，栈空直接失败
                if(st.empty()) return false;
                char top = st.top();
                st.pop();
                //判断是否配对
                if(c == ')' && top != '(') return false;
                if(c == '}' && top != '{') return false;
                if(c == ']' && top != '[') return false;
            }
        }
        //栈必须为空，有剩余左括号说明没匹配完
        return st.empty();
    }
};


另：
class Solution {
public:
    bool isValid(string s) {
        //只要还能找到配对，就循环替换
        while(s.find("()") != string::npos ||
              s.find("[]") != string::npos ||
              s.find("{}") != string::npos)
        {
            if(s.find("()") != string::npos){
                s.erase(s.find("()"),2);
            }
            else if(s.find("[]") != string::npos){
                s.erase(s.find("[]"),2);
            }
            else if(s.find("{}") != string::npos){
                s.erase(s.find("{}"),2);
            }
        }
        return s.empty();
    }
};


另：递归
//递归辅助函数
class Solution {
public:
    bool isValid(string s) {
        return dfs(s);
    }
};

bool dfs(string s){
    if(s=="") return true;
    for(int i=0;i+1<s.size();i++){
        if( (s[i]=='('&&s[i+1]==')') ||
            (s[i]=='['&&s[i+1]==']') ||
            (s[i]=='{'&&s[i+1]=='}') )
        {
            //删除i,i+1两个字符，递归剩下部分
            string next = s.substr(0,i)+s.substr(i+2);
            return dfs(next);
        }
    }
    return false;
}


