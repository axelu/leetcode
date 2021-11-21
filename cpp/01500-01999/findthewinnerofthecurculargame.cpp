
// 1823. Find the Winner of the Circular Game
// https://leetcode.com/problems/find-the-winner-of-the-circular-game/




class Solution {
private:
    // doubly linked list
    struct ListNode {
        int val;
        ListNode* prev;
        ListNode* next;
        ListNode(int x) : val(x), prev(nullptr), next(nullptr) {}
    };
public:
    int findTheWinner(int n, int k) {
        if( n == 1 ) return 1;

        ListNode* ln;
        ListNode* one = new ListNode(1);
        ListNode* prev = one;
        int i;
        for(i = 2; i <= n; ++i) {
            ln = new ListNode(i);
            ln->prev = prev;
            prev->next = ln;
            prev = ln;
        }
        prev->next = one;
        one->prev = prev;

        ln = one;

        ListNode* t;
        // int r = 1;
        while(ln->next != ln) {
            // cout << "round " << r << endl;
            for(i = 1; i < k; ++i) {
               ln = ln->next;
            }
            ln->prev->next = ln->next;
            ln->next->prev = ln->prev;
            t = ln;
            ln = ln->next;
            // cout << "evicting " << t->val << endl;
            delete t;
        }
        return ln->val;
    }
};
