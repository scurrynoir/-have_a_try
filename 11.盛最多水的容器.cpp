我的想法：暴力双循环
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int hi = height[i];
            for (int j = i + 1; j < n; j++) {
                int h = min(hi, height[j]);
                int area = h * (j - i);
                if(area > ans){
                    ans = area;
                }
            }
        }
        return ans;
    }
};
时间复杂度O(n^2))，小样例正确，力扣大数据直接超时。


  
最优解法：双指针 O(n)  
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int ans = 0;
        while(left < right){
            int h = min(height[left], height[right]);
            int area = h * (right - left);
            ans = max(ans, area);

            if(height[left] < height[right]){
                left++;
            }else{
                right--;
            }
        }
        return ans;
    }
};
原理：短板决定高度，移动长板，宽度变小，高度不会变大，面积只会更小；所以只能移动短板才有可能得到更大面积。
