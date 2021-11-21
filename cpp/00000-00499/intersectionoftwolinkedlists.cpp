
// 160. Intersection of two linked lists
// https://leetcode.com/problems/intersection-of-two-linked-lists/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if ( headA == nullptr ) return nullptr;
        if ( headB == nullptr ) return nullptr;

        unordered_set<ListNode*> u;
        while(headA != nullptr || headB != nullptr) {
            if (headA != nullptr) {
                auto success = u.insert(headA).second;
                if (!success) return headA;
                headA = headA->next;
            }
            if (headB != nullptr) {
                auto success = u.insert(headB).second;
                if (!success) return headB;
                headB = headB->next;
            }
        }

        return nullptr;
    }
};
