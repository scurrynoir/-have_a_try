我的想法：
struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 1.先遍历一遍，统计链表总长度len
        int len = 0;
        ListNode* cur = head;
        while(cur != nullptr){
            len++;
            cur = cur->next;
        }

        // 要删除的是第 idx 个节点（从0开始数）
        int idx = len - n;

        // 特殊：删除头结点，直接返回head->next
        if(idx == 0){
            ListNode* del = head;
            head = head->next;
            delete del;
            return head;
        }

        // 找到待删除节点的前驱 pre，pre停在idx‑1位置
        ListNode* pre = head;
        for(int i = 0; i < idx - 1; i++){
            pre = pre->next;
        }

        // 删除 pre 的下一个节点
        ListNode* del = pre->next;
        pre->next = pre->next->next;
        delete del;

        return head;
    }
};
