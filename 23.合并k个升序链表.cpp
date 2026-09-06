我的想法：两个一组合并，再与后面的合并，以此类推
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* dummy = new ListNode(0);
    ListNode* cur = dummy;

    while(l1 != nullptr && l2 != nullptr)
    {
        if(l1->val < l2->val)
        {
            cur->next = l1;
            l1 = l1->next;
        }
        else
        {
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }
    //剩下没走完的直接接上
    if(l1 != nullptr) cur->next = l1;
    if(l2 != nullptr) cur->next = l2;

    ListNode* ans = dummy->next;
    delete dummy;
    return ans;
}
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2){
        //上面的合并两链表代码放这里
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        //边界：没有链表直接返回空
        if(lists.empty()) return nullptr;

        //res保存已经合并完成的总链表，初始是lists[0]
        ListNode* res = lists[0];

        //从第1个开始，依次拿后面每一个链表，和res两两合并
        for(decltype(lists.size()) i = 1; i < lists.size(); ++i)
        {
            // 把旧res 和 lists[i]合并，得到新res
            res = mergeTwoLists(res, lists[i]);
        }
        return res;
    }
};


