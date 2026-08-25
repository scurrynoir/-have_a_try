我的想法：vector拆
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
    bool dfs(string &s, string &p, int j, vector<char> cur){
        //模式串走完，对比cur和s
        if(j == p.size()){
            if(cur.size() != s.size()) return false;
            for(int k=0;k<s.size();k++){
                if(cur[k] != s[k]) return false;
            }
            return true;
        }

        bool nextStar = (j+1 < p.size() && p[j+1] == '*');
        if(nextStar){
            char ch = p[j];
            //分支1：x*匹配0次，跳过x*
            if(dfs(s,p,j+2, cur)) return true;

            //分支2：匹配一次ch，继续可以再匹配（j不变）
            cur.push_back(ch);
            //剪枝：cur长度超过s就不要再往下走
            if(cur.size() <= s.size()){
                if(dfs(s,p,j, cur)) return true;
            }
            return false;
        }else{
            //普通字符 或者 .
            if(p[j] == '.'){
                //.必须匹配当前s对应位置的真实字符！不能随便塞'A'
                //这里关键：cur长度不能超过s
                if(cur.size() >= s.size()) return false;
                cur.push_back(s[cur.size()]); 
            }else{
                cur.push_back(p[j]);
            }
            return dfs(s,p,j+1, cur);
        }
    }

    bool isMatch(string s, string p) {
        vector<char> tmp;
        return dfs(s,p,0,tmp);
    }
};

