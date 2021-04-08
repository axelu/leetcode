
// Linked List Cycle II
// https://leetcode.com/problems/linked-list-cycle-ii/



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
private:
    int vid[200001]; // unique value index
public:
    ListNode *detectCycle(ListNode *head) {
        // Note: nothing states values are unique,
        //       hence we must assume they are not!

        // get unique values
        set<int> uv;
        ListNode * t = head;
        for(int i = 0; i < 10000; ++i) {
            if( t == nullptr ) return nullptr;
            if( t->next == t ) return t;
            uv.insert(t->val);
            t = t->next;
        }

        // if we are here, then there is a cycle

        // transform unique values into a unique value index
        int k = 0;
        for(auto it = begin(uv); it != end(uv); ++it) {
            vid[*it + 100000] = k;
            ++k;
        }

        vector<vector<ListNode*>> a(k, vector<ListNode*>());
        vector<ListNode*> p;
        while( true ) {
            // have we seen next already?
            p = a[vid[head->next->val + 100000]];
            for(auto ln : p)
                if( ln == head->next ) return head->next;

            // insert ourselfs
            a[vid[head->val + 100000]].push_back(head);

            head = head->next;
        }

        return nullptr;
    }
};
