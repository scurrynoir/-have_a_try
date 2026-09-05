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

正解：快慢指针
fast 先往前走 n 步；然后 fast、slow 一起走，fast 走到 null 时，slow 就是要删节点的前驱。


class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 虚拟头结点，完美规避删除头结点特殊判断
        ListNode* dummy = new ListNode(0, head);
        ListNode* fast = dummy;
        ListNode* slow = dummy;

        // fast先走n步
        for(int i = 0; i < n; i++){
            fast = fast->next;
        }
        // fast、slow一起往后走，直到fast走到末尾nullptr
        while(fast->next != nullptr){
            fast = fast->next;
            slow = slow->next;
        }
        // slow->next 就是要删除的节点
        ListNode* del = slow->next;
        slow->next = slow->next->next;
        delete del;

        ListNode* ans = dummy->next;
        delete dummy;
        return ans;
    }
};

