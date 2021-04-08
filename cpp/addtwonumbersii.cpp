
// 445. Add Two Numbers II
// day 7 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/564/week-1-november-1st-november-7th/3522/
// https://leetcode.com/problems/add-two-numbers-ii/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
private:
    stack<int> listNodeToStack(ListNode* l) {
        stack<int> stck;
        ListNode* t = l;
        while( t != nullptr ) {
            stck.push(t->val);
            t = t->next;
        }
        return stck;
    }

public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if( l1->val == 0 ) return l2;
        if( l2->val == 0 ) return l1;

        stack<int> s1 = listNodeToStack(l1);
        stack<int> s2 = listNodeToStack(l2);

        int i1,i2,k;
        int of = 0; // overflow
        ListNode* r = nullptr;
        ListNode* t;
        while(!s1.empty() || !s2.empty() || of != 0) {

            if( !s1.empty() ) {
                i1 = s1.top();
                s1.pop();
            } else {
                i1 = 0;
            }

            if( !s2.empty() ) {
                i2 = s2.top();
                s2.pop();
            } else {
                i2 = 0;
            }

            k = i1 + i2 + of;
            if( k > 9 ) {
                of = 1;
                k = k % 10;
            } else {
                of = 0;
            }

            t = new ListNode(k,r);
            r = t;
        }

        return r;
    }
};
