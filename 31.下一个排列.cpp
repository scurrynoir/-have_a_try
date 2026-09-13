我的想法：用sort
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i = n - 2;

        // 1. 从后往前找第一个升序相邻对 nums[i] < nums[i+1]
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        if (i >= 0) {
            // 2. 从后往前找第一个比 nums[i] 大的数
            int j = n - 1;
            while (nums[j] <= nums[i]) {
                j--;
            }
            // 3. 交换两个位置的元素
            swap(nums[i], nums[j]);
        }

        // 4. 把 i 右侧的部分升序排序，得到最小的后缀
        sort(nums.begin() + i + 1, nums.end());
    }
};


标答：
## （原地算法）

### 算法四步走

1. **从后往前找 i**：第一个满足 `nums[i] < nums[i+1]` 的位置；
2. **从后往前找 j**：在 i 右侧，第一个满足 `nums[j] > nums[i]` 的位置；
3. **交换 nums [i] 和 nums [j]**；
4. **反转 i 右侧的所有元素**（此时右侧天然降序，反转后就是升序，即最小的后缀）。

如果第一步找不到 i（全降序），直接反转整个数组。

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i = n - 2;

        // 第一步：从后往前找第一个升序相邻对 nums[i] < nums[i+1]
        // 循环结束后，i 右侧的所有元素天然是「严格降序」
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        if (i >= 0) {
            // 第二步：从后往前找第一个比 nums[i] 大的数 nums[j]
            int j = n - 1;
            while (nums[j] <= nums[i]) {
                j--;
            }
            // 第三步：交换 i 和 j 位置的元素
            swap(nums[i], nums[j]);
        }

        // 第四步：反转 i 右侧的所有元素
        // 右侧本来就是降序，反转后直接变成升序，得到最小的后缀
        reverse(nums.begin() + i + 1, nums.end());
    }
};
