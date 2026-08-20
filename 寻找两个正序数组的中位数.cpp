我的想法：暴力合并
#include <vector>
using namespace std;
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> merge;
        int i = 0, j = 0;      //双指针归并
        while(i < nums1.size() && j < nums2.size())
        {
            if(nums1[i] < nums2[j])
                merge.push_back(nums1[i++]);      //先使用 i 当下标取值，执行完之后 i = i+1
            else
                merge.push_back(nums2[j++]);
        }
        
      
        //把剩余尾巴接上
        while(i < nums1.size()) merge.push_back(nums1[i++]);  
        while(j < nums2.size()) merge.push_back(nums2[j++]);

        int total = merge.size();
        if(total % 2 == 1)
        {
            return merge[total / 2];
        }
        else
        {
            return (merge[total/2 - 1] + merge[total/2]) / 2.0;
        }
    }
};
开辟新数组，时间 (O(m+n))





