我的思路：n/k为一组，调用函数实现反转
Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* REVERSE(ListNode* head, int n){
    ListNode* n = head;ListNode* nn = n->next;
    for (int i = 0;i < n;i++){
        
        
    }
    

}


class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        int n=0;
        ListNode* p = head;
        while (p != nullptr){
            n++;
            p = p->next;
        }

        for (int i = 0; i < n/k; i++){
            
        }

        
    }
};


正解：
1. 用**虚拟头结点 dummy**统一处理头结点翻转的情况，不用特判第一组。
2. 用`pre`指针指向每组的前一个节点（上一组的尾部）。
3. 每次翻转`pre`后面的 k 个节点：把`start`后面的节点一个个 “头插” 到`pre`后面，完成组内翻转。
4. 翻转完一组，`pre`移动到本组新的尾部（也就是原来的 start），继续下一组。
5. 剩余不足 k 个节点，直接结束。
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        // 虚拟头结点，避免头结点特判
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* pre = dummy;

        while (true) {
            // 检查剩余节点是否够k个
            ListNode* end = pre;
            for (int i = 0; i < k; i++) {
                end = end->next;
                if (end == nullptr) {
                    // 不足k个，直接返回
                    return dummy->next;
                }
            }

            ListNode* start = pre->next; // 本组第一个节点，翻转后变成本组尾
            ListNode* curr = start->next;

            // 头插法翻转k-1次，完成k个节点翻转
            for (int i = 0; i < k - 1; i++) {
                start->next = curr->next;
                curr->next = pre->next;
                pre->next = curr;
                curr = start->next;
            }

            // pre移动到下一组的前一个节点（本组翻转后的尾）
            pre = start;
        }
    }
};
