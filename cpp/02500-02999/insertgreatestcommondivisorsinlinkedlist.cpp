
// 2807. Insert Greatest Common Divisors in Linked List
// https://leetcode.com/problems/insert-greatest-common-divisors-in-linked-list/



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
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {

        ListNode* prev = head;
        ListNode* curr = head->next;
        while( curr != nullptr ) {
            int _gcd = gcd(prev->val,curr->val);
            ListNode* ln = new ListNode(_gcd,curr);
            prev->next = ln;
            prev = curr;
            curr = curr->next;
        }

        return head;
    }
};
