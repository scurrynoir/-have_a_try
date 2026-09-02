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
