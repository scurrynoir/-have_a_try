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
