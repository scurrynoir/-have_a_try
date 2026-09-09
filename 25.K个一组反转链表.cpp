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
