我的思路:递归 卒

## 标准解法：回溯法（DFS）

### 核心思路

用深度优先搜索，一边构造字符串一边保证合法性：

1. **左括号**：只要数量还没到`n`，就可以加左括号；
2. **右括号**：只有当右括号数量 **小于** 左括号数量时，才能加右括号（保证不会出现`)(`这种非法情况）；
3. 当字符串长度等于`2*n`时，说明构造完成，加入结果集。

### 完整可运行代码

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        // 回溯：当前字符串、左括号数、右括号数、总对数n、结果集
        dfs("", 0, 0, n, res);
        return res;
    }

private:
    void dfs(string path, int left, int right, int n, vector<string>& res) {
        // 终止条件：长度达到2n，加入结果
        if (path.size() == 2 * n) {
            res.push_back(path);
            return;
        }

        // 可以加左括号：左括号还没用完
        if (left < n) {
            dfs(path + "(", left + 1, right, n, res);
        }

        // 可以加右括号：右括号数量 < 左括号数量
        if (right < left) {
            dfs(path + ")", left, right + 1, n, res);
        }
    }
};

// 本地测试main
int main() {
    Solution sol;
    int n = 3;
    vector<string> ans = sol.generateParenthesis(n);
    
    cout << "n=" << n << " 的合法括号组合：" << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
