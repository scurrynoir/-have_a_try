我的想法：三重暴力循环
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        int n = nums.size();
        for (int i = 0; i < n; i++){
            for (int j = i + 1; j < n; j++){
                for (int k = j + 1; k < n; k++){ 
                    if(nums[i] + nums[j] + nums[k] == 0){
                        vector<int> tmp;
                        tmp.push_back(nums[i]);
                        tmp.push_back(nums[j]);
                        tmp.push_back(nums[k]);
                        ans.push_back(tmp);
                    }
                }
            }
        }
        return ans;
    }
};
- O (n³)，数据稍大直接超时
- 输入 `[-1,-1,0,1]` 会产生重复 `[-1,0,1]`，没有去重，力扣判错

标准解法：排序 + 固定 i + 双指针（O (n²)）
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        int n = nums.size();
        sort(nums.begin(), nums.end()); // 先排序
        
        for(int i = 0; i < n; i++)
        {
            // i去重：和上一个一样就跳过，防止重复答案
            if(i > 0 && nums[i] == nums[i-1]) continue;

            int left = i + 1;
            int right = n - 1;
            while(left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];
                if(sum == 0)
                {
                    ans.push_back({nums[i], nums[left], nums[right]});
                    // left指针去重
                    while(left < right && nums[left]==nums[left+1]) left++;
                    // right指针去重
                    while(left < right && nums[right]==nums[right-1]) right--;
                    
                    left++;
                    right--;
                }
                else if(sum < 0)
                {
                    sum太小，需要变大 → left右移
                    left++;
                }
                else
                {
                    sum太大，需要变小 → right左移
                    right--;
                }
            }
        }
        return ans;
    }
};


另：哈希表打法：
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        int n = nums.size();
        sort(nums.begin(), nums.end()); // 排序主要为了方便去重
        
        for(int i = 0; i < n; i++)
        {
            // i位置去重，跳过相同数字，避免重复
            if(i > 0 && nums[i] == nums[i-1]) continue;

            unordered_set<int> st;
            int target = -nums[i];

            for(int j = i + 1; j < n; j++)
            {
                int need = target - nums[j];
                if(st.count(need))
                {
                    ans.push_back({nums[i], need, nums[j]});
                    // j去重：跳过后面相等元素，防止重复
                    while(j + 1 < n && nums[j] == nums[j+1])
                    {
                        j++;
                    }
                }
                st.insert(nums[j]);
            }
        }
        return ans;
    }
};




