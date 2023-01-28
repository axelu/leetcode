
// 2487. Remove Nodes From Linked List
// https://leetcode.com/problems/remove-nodes-from-linked-list/



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
public:
    ListNode* removeNodes(ListNode* head) {


        ListNode* nd = head;

        stack<ListNode*> stck;
        while( nd != nullptr ) {

            while( !stck.empty() && stck.top()->val < nd->val )
                stck.pop();

           if( !stck.empty() )
               stck.top()->next = nd;
            else
                head = nd;

            stck.push(nd);
            nd = nd->next;
        }

        return head;
    }
};
