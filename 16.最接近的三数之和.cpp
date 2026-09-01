我的想法：暴力
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        // 先随便拿一组作为初始答案
        int ans = nums[0] + nums[1] + nums[2];

        // 三重暴力枚举 i<j<k，避免重复组合
        for(int i = 0; i < n; i++)
        {
            for(int j = i + 1; j < n; j++)
            {
                for(int k = j + 1; k < n; k++)
                {
                    int sum = nums[i] + nums[j] + nums[k];
                    // 当前sum离target更近，就更新答案
                    if( abs(sum - target) < abs(ans - target) )
                    {
                        ans = sum;
                    }
                }
            }
        }
        return ans;
    }
};


最优：排序 + 双指针（AC 版本）
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int ans = nums[0] + nums[1] + nums[2];

        for(int i = 0; i < n; i++)
        {
            int left = i + 1;
            int right = n - 1;
            while(left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];
                if( abs(sum-target) < abs(ans-target) )
                    ans = sum;

                if(sum < target) left++;     // 和太小，左指针右移变大
                else right--;                // 和太大，右指针左移变小
            }
        }
        return ans;
    }
};
