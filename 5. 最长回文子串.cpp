我的垃圾思路：两头往中间缩
class Solution {
public:
    string longestPalindrome(string s) {
        int n=s.length();
        int i=0;int j=n-1;int max=0;int p=i;int q=j;
        while (p<q){
            while (i<j && s[i]==s[j]) i++;j--;
            int m=j-i;
            if (m>max) max=n;
        }
        return max;        <——大错
    }
};

