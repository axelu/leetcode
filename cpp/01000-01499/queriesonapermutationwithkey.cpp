
// 1409. Queries on a Permutation With Key
// https://leetcode.com/problems/queries-on-a-permutation-with-key/



class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {

        // doubly linked list
        struct ListNode {
            int val;
            ListNode* prev;
            ListNode* next;
            ListNode(int x) : val(x), prev(nullptr), next(nullptr) {}
        };

        ListNode* tail;
        ListNode* head;

        int i,k;
        ListNode* node;
        ListNode* prev = nullptr;
        for(i = 1; i <=m; ++i) {
            node = new ListNode(i);
            if( prev == nullptr ) {
                head = node;
            } else {
                node->prev = prev;
                prev->next = node;
            }
            prev = node;
            if( i == m ) tail = node;
        }

        vector<int> ans;
        for(i = 0; i < queries.size(); ++i) {
            k = 0;
            node = head;
            while(true) {
                if( node->val == queries[i] ) break;
                ++k;
                node = node->next;
            }
            ans.push_back(k);
            if( node == head ) continue;
            if( node == tail ) {
                node->prev->next = nullptr;
                tail = node->prev;
            } else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            node->prev = nullptr;
            node->next = head;
            head->prev = node;
            head = node;
        }
        return ans;
    }
};
