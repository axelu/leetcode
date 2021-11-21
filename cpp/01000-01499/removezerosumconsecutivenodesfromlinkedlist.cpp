
// 1171. Remove Zero Sum Consecutive Nodes from Linked List
// https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/




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
    ListNode* removeZeroSumSublists(ListNode* head) {
        if( head == nullptr )
            return nullptr;
        if( head->next == nullptr ) {
            if( head->val != 0 )
                return head;
            else
                nullptr;
        }


        ListNode* node = head;
        unordered_map<int,ListNode*> um;
        unordered_map<int,ListNode*>::iterator f;
        ListNode* del;
        int sum = 0, t;
        while( node != nullptr ){
            sum += node->val;
            if( sum == 0 ) {
                // we can delete everything so far
                head = node->next;
                um.clear();
            } else {
                // if we have seen the same sum before,
                // we have balance
                f = um.find(sum);
                if( f != um.end() ) {

                    // delete all nodes in between and the
                    // prefix sums we recorded
                    del = f->second->next;
                    t = sum;
                    while( del != node ){
                        t += del->val;
                        um.erase(t);
                        del = del->next;
                    }

                    f->second->next = node->next;

                } else
                    um.insert({sum,node});
            }
            node = node->next;
        }


        return head;
    }
};
