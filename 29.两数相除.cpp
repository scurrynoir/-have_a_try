我的想法：连加 超时

## 标准解法：倍增法（快速加）

### 核心思路

1. **统一转负数计算**：避免 `INT_MIN` 转正数溢出（因为 INT_MIN 的绝对值比 INT_MAX 大）。
2. **倍增思想**：每次把除数翻倍（加自身），同时计数也翻倍，快速逼近被除数，把时间复杂度降到 **O(log n)**。
3. **最后处理符号**：同号为正，异号为负。
4. **特判溢出**：`INT_MIN / -1` 直接返回 `INT_MAX`

#include <iostream>
#include <climits>
using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        // 唯一溢出场景：INT_MIN 除以 -1
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        // 记录最终符号：同号为正，异号为负
        int sign = 1;
        if ((dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0)) {
            sign = -1;
        }

        // 全部转成负数，避免正数溢出
        if (dividend > 0) dividend = -dividend;
        if (divisor > 0) divisor = -divisor;

        int ans = 0;
        // 核心：倍增法快速累加
        while (dividend <= divisor) { // 注意都是负数，越小代表绝对值越大
            int temp = divisor;  // 当前累加的除数
            int count = 1;       // 当前对应的倍数

            // 倍增：temp翻倍，count也翻倍，直到再加就超过被除数
            while (temp >= dividend - temp) { // 用减法防止temp+temp溢出
                temp += temp;
                count += count;
            }

            dividend -= temp;
            ans += count;
        }

        return sign * ans;
    }
};

// 本地测试
int main() {
    Solution sol;
    cout << sol.divide(10, 3) << endl;          // 3
    cout << sol.divide(7, -3) << endl;          // -2
    cout << sol.divide(6, 3) << endl;           // 2
    cout << sol.divide(INT_MIN, -1) << endl;    // 2147483647
    cout << sol.divide(INT_MIN, 2) << endl;     // -1073741824
    return 0;
}
