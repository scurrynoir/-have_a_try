#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


————————————————————————————————————————————————————————————————————————————————我的想法：——————————————————————————————————————————————————————————————————————————
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//倒序取出节点，存vector
vector<int> getNum(ListNode* head)
{
    vector<int> tmp;
    ListNode* p = head;
    while(p != nullptr)
    {
        tmp.push_back(p->val);
        p = p->next;
    }
    // tmp现在 [2,4,3]，反转变成高位在前 [3,4,2]
    reverse(tmp.begin(), tmp.end());
    return tmp;
}

//把vector数字转成long long（只能很短！长链表溢出）
long long vecToLong(vector<int>& v)
{
    long long num = 0;
    for(auto x : v)
    {
        num = num * 10 + x;
    }
    return num;
}

//数字再转回逆序链表
ListNode* longToList(long long n)
{
    ListNode* dummy = new ListNode();
    ListNode* cur = dummy;
    if(n == 0)
    {
        cur->next = new ListNode(0);
        return dummy->next;
    }
    while(n > 0)
    {
        int d = n %10;
        cur->next = new ListNode(d);
        cur = cur->next;
        n = n / 10;
    }
    return dummy->next;
}


class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        vector<int> v1 = getNum(l1);
        vector<int> v2 = getNum(l2);

        long long a = vecToLong(v1);
        long long b = vecToLong(v2);
        long long res = a + b;

        return longToList(res);
    }
};


int main()
{
    // 2->4->3  342
    ListNode* l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);

    //5->6->4 465
    ListNode* l2 = new ListNode(5);
    l2->next = new ListNode(6);
    l2->next->next = new ListNode(4);

    Solution s;
    ListNode* ans = s.addTwoNumbers(l1,l2);
    while(ans)
    {
        cout << ans->val << " ";
        ans = ans->next;
    }
    return 0;
}
## 致命缺陷（力扣不能用这个解法）：
`long long`最大只能存 922 亿左右。
如果链表有 20 位以上数字，`long long`直接溢出，数值错乱。


————————————————————————————————————————————————————————————————————另一种写法：放到数组中————————————————————————————————————————————————————————————————————————————————
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 链表 → 高位在前的string
string listToString(ListNode* head)
{
    vector<int> tmp;
    ListNode* p = head;
    while(p)
    {
        tmp.push_back(p->val);
        p = p->next;
    }
    reverse(tmp.begin(), tmp.end()); // 变成高位在前

    string s;
    for(int x : tmp)
    {
        s += (char)('0' + x);
    }
    return s;
}

// 大数字符串加法，输入高位在前，返回高位在前
string stringAdd(string a, string b)
{
    int i = a.size()-1;
    int j = b.size()-1;
    int carry = 0;
    string res;

    while(i >=0 || j >=0 || carry >0)
    {
        int v1 = i >=0 ? a[i]-'0' : 0;
        int v2 = j >=0 ? b[j]-'0' : 0;
        int sum = v1 + v2 + carry;
        carry = sum / 10;
        res.push_back( (sum%10) + '0' );
        i--; j--;
    }
    reverse(res.begin(), res.end()); //转回高位在前
    return res;
}

//高位在前string → 逆序链表（题目输出格式，低位在表头）
ListNode* stringToList(string s)
{
    ListNode* dummy = new ListNode();
    ListNode* cur = dummy;
    // s高位在前，要从后往前拿，先拿个位
    for(int i = s.size()-1; i >= 0; i--)
    {
        int num = s[i] - '0';
        cur->next = new ListNode(num);
        cur = cur->next;
    }
    return dummy->next;
}


class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        string s1 = listToString(l1);
        string s2 = listToString(l2);

        string sumStr = stringAdd(s1,s2);
        return stringToList(sumStr);
    }
};

int main()
{
    // l1 = [2,4,3] →342
    ListNode* l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);

    // l2 = [5,6,4] →465
    ListNode* l2 = new ListNode(5);
    l2->next = new ListNode(6);
    l2->next->next = new ListNode(4);

    Solution sol;
    ListNode* ans = sol.addTwoNumbers(l1,l2);

    while(ans)
    {
        cout << ans->val << " ";
        ans = ans->next;
    }
    return 0;
}

字符串大数版（本代码）  支持无限长度大数，可以 AC多轮拷贝反转 ；但代码长，效率低


————————————————————————————————————————————————————————————————————————————————————标答：———————————————————————————————————————————————————————————————————————————————————
struct ListNode {
    int val;                     //节点存数字0‑9
    ListNode *next;              //指向下一个节点
    ListNode() : val(0), next(nullptr) {}                   //无参构造 val=0，next空
    ListNode(int x) : val(x), next(nullptr) {}              //给val赋值x，next=nullptr
    ListNode(int x, ListNode *next) : val(x), next(next){}  //同时赋值val和next
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {   // l1、l2是两个链表头指针，返回相加后新链表头指针
        ListNode* dummy = new ListNode();// 哨兵头结点
        ListNode* cur = dummy;
        int carry = 0;                   //进位

        while(l1 != nullptr || l2 != nullptr || carry != 0)
        {
            int v1 = (l1 != nullptr) ? l1->val : 0;  //三目运算符
            int v2 = (l2 != nullptr) ? l2->val : 0;

            int sum = v1 + v2 + carry;
            carry = sum / 10;        //计算进位
            int digit = sum % 10;    //当前位

            cur->next = new ListNode(digit);   // 新建节点，挂到 cur 后面，加到结果链表。
            cur = cur->next;

            if(l1 != nullptr) l1 = l1->next;    // l1 不为空就往后走一步；如果已经 nullptr，不动。
            if(l2 != nullptr) l2 = l2->next;    // 返回哨兵的下一个，就是真正结果链表的第一个有效节点，不能 return dummy，dummy 本身是哑节点。
        }
        return dummy->next;
    }
};



