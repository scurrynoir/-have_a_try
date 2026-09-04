我的思路：钉住i，新target用17的思路
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        int n = nums.size();
        // 排序，直接调用sort，可不用手写冒泡
        sort(nums.begin(), nums.end());

        // 固定第一个数 i
        for(int i = 0; i < n; i++)
        {
            // i层去重：i和上一个i相同，跳过
            if(i > 0 && nums[i] == nums[i-1]) continue;

            // 固定第二个数 j，j必须在i后面 j = i+1
            for(int j = i + 1; j < n; j++)
            {
                // j层去重
                if(j > i+1 && nums[j] == nums[j-1]) continue;

                long long target1 = (long long)target - nums[i] - nums[j];
                int l = j + 1;
                int r = n - 1;

                while(l < r)
                {
                    //  每次循环内部重新算两数之和
                    long long sumLR = (long long)nums[l] + nums[r];
                    if(sumLR < target1)
                    {
                        l++;
                    }
                    else if(sumLR > target1)
                    {
                        r--;
                    }
                    else
                    {
                        // 找到一组解
                        ans.push_back({nums[i], nums[j], nums[l], nums[r]});
                        // l r去重
                        while(l < r && nums[l]==nums[l+1]) l++;
                        while(l < r && nums[r]==nums[r-1]) r--;
                        // 收缩指针
                        l++;
                        r--;
                    }
                }
            }
        }
        return ans;
    }
};
