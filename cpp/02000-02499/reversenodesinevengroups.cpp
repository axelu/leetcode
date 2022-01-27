
// 2074. Reverse Nodes in Even Length Groups
// https://leetcode.com/problems/reverse-nodes-in-even-length-groups/




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
    void reverseList(ListNode* A, ListNode* B, ListNode* C, ListNode* D) {
        /*
        cout << "A " << A->val << endl;
        cout << "B " << B->val << endl;
        cout << "C " << C->val << endl;
        if( D != nullptr ) cout << "D " << D->val << endl;
        else cout << "D nullptr" << endl;
        */

        // A → (B → ... → C) → D.

        ListNode *head = B;
        ListNode *p = nullptr;
        while( head != D ) {
            ListNode *t = head->next;
            head->next = p;
            p = head;
            head = t;
        }

        A->next = C;
        B->next = D;
    }

public:
    ListNode* reverseEvenLengthGroups(ListNode* head) {

        int i  = 0;
        int g  = 1;
        ListNode* A;  // last node of prior group
        ListNode* B;  // 1st node of current group
        ListNode* C;  // last node of current group
        ListNode* D;  // 1st node of next group

        int t = 0;    // number nodes in group
        int a = 0;    // last node of prior group (index)
        int b = 1;    // 1st node of current group (index)
        int c = 1;    // last node of current group (index)
        int d = 1;    // 1st node of next group (index)
        ListNode* prev = nullptr;
        ListNode* n = head;

        while( n != nullptr ) {
            ++i;++t;
            // cout << "i " << i << " g " << g << endl;

            if( i == c || ( n->next == nullptr && t%2 == 0 ) ) {
                if( t%2 == 0 ) {
                    c = i;   C = n;
                    d = i+1; D = n->next;
                    // cout << "reverse current group g " << g << endl;
                    // cout << "a " << a << " b " << b << " c " << c << " d " << d << endl;
                    reverseList(A,B,C,D);
                    n = B;
                }
                a = i;   A = n;
                b = i+1; B = n->next;
                ++g;t=0;
                c += g;
                d = c+1;
            }
            prev = n;
            n = n->next;
        }

        return head;
    }
};
