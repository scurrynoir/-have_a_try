我的思路：链表
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 字母链表节点：保存一个字符串结果
struct StrNode {
    string s;
    StrNode* next;
    StrNode(string str) : s(str), next(nullptr) {}
};

// 【你说的：数字作为哨兵节点】
struct MapNode {
    int digit;         // 哨兵存数字
    char ch;
    MapNode* next;
    MapNode(int d) : digit(d), ch(0), next(nullptr) {}
    MapNode(char c) : digit(-1), ch(c), next(nullptr) {}
};

// 构建映射：数字哨兵，后面挂字母链表
MapNode* buildMap() {
    MapNode* head = new MapNode(-1);
    // 2
    MapNode* n2 = new MapNode(2);
    n2->next = new MapNode('a');
    n2->next->next = new MapNode('b');
    n2->next->next->next = new MapNode('c');

    //3
    MapNode* n3 = new MapNode(3);
    n3->next = new MapNode('d');
    n3->next->next = new MapNode('e');
    n3->next->next->next = new MapNode('f');

    //4
    MapNode* n4 = new MapNode(4);
    n4->next = new MapNode('g');
    n4->next->next = new MapNode('h');
    n4->next->next->next = new MapNode('i');

    head->next = n2;
    n2->next->next->next->next = n3;
    n3->next->next->next->next = n4;
    return head;
}

// 根据数字，拿到它的字母链表
MapNode* getCharList(MapNode* mapHead, int num) {
    MapNode* p = mapHead->next;
    while(p != nullptr){
        if(p->digit == num) return p->next;
        p = p->next->next->next->next;
    }
    return nullptr;
}

// 把链表结果转为vector
vector<string> listToVec(StrNode* resHead) {
    vector<string> ans;
    StrNode* p = resHead->next;
    while(p){
        ans.push_back(p->s);
        p = p->next;
    }
    return ans;
}

// 释放字符串链表
void freeStrList(StrNode* head){
    StrNode* cur = head;
    while(cur){
        StrNode* del = cur;
        cur = cur->next;
        delete del;
    }
}

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> empty;
        if(digits.empty()) return empty;

        MapNode* mapHead = buildMap();

        // 结果链表，哨兵头
        StrNode* resHead = new StrNode("");

        for(char ch : digits)
        {
            int num = ch - '0';
            MapNode* charList = getCharList(mapHead, num);
            if(charList == nullptr) continue;

            // 保存旧的结果链表
            StrNode* old = resHead->next;
            resHead->next = nullptr;

            // 双重循环拼接
            StrNode* pOld = old;
            while(pOld != nullptr)
            {
                MapNode* pChar = charList;
                while(pChar != nullptr)
                {
                    string newStr = pOld->s + pChar->ch;
                    //头插
                    StrNode* newNode = new StrNode(newStr);
                    newNode->next = resHead->next;
                    resHead->next = newNode;
                    pChar = pChar->next;
                }
                pOld = pOld->next;
            }
            freeStrList(old);
        }

        vector<string> ret = listToVec(resHead);
        freeStrList(resHead);
        return ret;
    }
};


标准回溯写法（力扣 AC，对比记忆）：
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        // res：存储最终全部组合结果
        vector<string> res;

        // 特判：输入是空字符串，直接返回空结果
        if(digits.empty()) return res;

        // mp下标对应电话号码数字：mp[2]就是"abc"，mp[0]、mp[1]为空字符串
        vector<string> mp={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

        // path：DFS递归过程，保存当前正在拼接的路径字符串
        string path;

        // function<void(int)> 定义一个可调用对象，接收int参数，无返回值；lambda表达式实现dfs
        // [&] 捕获列表：以引用方式捕获外部所有变量(res, digits, mp, path)，lambda内部可以修改外部变量
        function<void(int)> dfs=[&](int idx){
            // 递归终止条件：idx等于digits总长度，代表一条完整组合已经生成完毕
            if(idx==digits.size()){
                res.push_back(path); // 把当前路径保存到答案集合
                return;              // 返回，回溯
            }

            // 当前处理的字符转成数字，例如 '2'-'0' → 2
            int num=digits[idx]-'0';

            // 遍历这个数字对应的每一个字母
            for(char c:mp[num]){
                path.push_back(c);   // 选择：把字符c加入当前路径
                dfs(idx+1);          // 递归，处理下一个数字位置
                path.pop_back();     // 回溯！撤销上一步选择，恢复path，尝试下一个字母
            }
        };

        dfs(0); // 从下标0开始启动深度优先搜索

        return res; // 返回全部字母组合
    }
};

