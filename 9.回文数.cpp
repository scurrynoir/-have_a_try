我的想法：转字符串放入vector
class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0) return false;
        string l = to_string(x);
        int n = l.length();
        vector<char> arr1,arr2;
        for(int i = 0; i < n; i++){
            arr1.push_back(l[i]);
        }
        for(int i = n-1; i >= 0; i--){ //i>=0，不能i>0
            arr2.push_back(l[i]);
        }
        return arr1 == arr2;
    }
};


另：
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        //负数直接不是回文
        if(x < 0) return false;
        string s = to_string(x);
        int n = s.length();
        int l = 0, r = n - 1;
        while(l < r)
        {
            if(s[l] != s[r])
                return false;
            l++;
            r--;
        }
        return true;
    }
};



