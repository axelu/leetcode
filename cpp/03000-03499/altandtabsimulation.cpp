
// 3237. Alt and Tab Simulation
// https://leetcode.com/problems/alt-and-tab-simulation/





class Solution {
private:
    // doubly linked list
    struct ListNode {
        int val;
        ListNode* prev;
        ListNode* next;
        ListNode(int v) : val(v), prev(nullptr), next(nullptr) {}
    };

    unordered_map<int,ListNode*> listNodes;

public:
    vector<int> simulationResult(vector<int>& windows, vector<int>& queries) {
        int n = windows.size();
        if( n == 1 )
            return {1};

        // build the initial list
        ListNode* head;
        ListNode* prev = nullptr;
        for(int i = 0; i < n; ++i) {
            ListNode* ln = new ListNode(windows[i]);
            if( i == 0 ) {
                head = ln;
            } else {
                prev->next = ln;
                ln->prev = prev;
            }
            listNodes[windows[i]] = ln;
            prev = ln;
        }

        // process queries
        for(int q: queries) {
            ListNode* ln = listNodes[q];
            // we need to move ln to front of our list
            // ls is already the head of our list
            if( ln == head ) {
                continue;

            // ln is the tail of our list
            } else if( ln->next == nullptr ) {
                ListNode* prev = ln->prev;
                prev->next = nullptr;

                head->prev = ln;
                ln->next = head;
                ln->prev = nullptr;

            // ln is somewhere in the our list
            } else {
                ListNode* prev = ln->prev;
                ListNode* next = ln->next;

                prev->next = next;
                next->prev = prev;

                head->prev = ln;
                ln->next = head;
                ln->prev = nullptr;
            }
            head = ln;
        }

        // collect final order of windows
        vector<int> ans(n);
        int i = 0;
        ListNode* nd = head;
        while( nd != nullptr ) {
            ans[i] = nd->val;
            ++i;
            nd = nd->next;
        }

        return ans;
    }
};
