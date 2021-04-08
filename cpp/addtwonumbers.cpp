#include <iostream>
#include <cassert>
#include <stack>
#include <cmath>

// Definition of a singly-linked list 
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

using namespace std;

// https://leetcode.com/problems/add-two-numbers/

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        if ( l1 == nullptr ) return l2;
        if ( l2 == nullptr ) return l1;

        ListNode* rn = new ListNode( l1->val + l2->val );

        int m = 0;

        if ( rn->val >= 10 ) {
            m = 1;
            rn->val = rn->val - 10;
        }

        ListNode* n1 = l1->next;
        ListNode* n2 = l2->next;
        ListNode* cn = rn;
        while ( m == 1 || n1 != nullptr || n2 != nullptr ) {
            cn->next = new ListNode( m );
            cn = cn->next;
            if ( n1 != nullptr ) {
                cn->val = cn->val + n1->val;
                n1 = n1->next;
            }
            if ( n2 != nullptr ) {
                cn->val = cn->val + n2->val;
                n2 = n2->next;
            }
            if ( cn->val >= 10 ) {
                m = 1;
                cn->val = cn->val - 10;
            } else {
                m = 0;
            }
            if ( m == 0 ) {
                if ( n1 == nullptr && n2 != nullptr ) {
                    cn->next = n2;
                    break;
                } else if ( n1 != nullptr && n2 == nullptr ) {
                    cn->next = n1;
                    break;
                }
            }
        }

        return rn;
    }
};

int main() {

    Solution s;

    // 342
    // ListNode l1_1 = ListNode(3);
    // ListNode l1_2 = ListNode(4, &l1_1);
    // ListNode l1_3 = ListNode(2, &l1_2);
    // ListNode* l1 = &l1_3;
    
    ListNode* ll = s._intToListNode(342);

    assert(ll->val == 2);
    ListNode * l2 = ll->next;
    assert(l2->val == 4);
    ListNode* l3 = l2->next;
    assert(l3->val == 3);

    assert(s._listNodeToInt(ll) == 342);


    ListNode* lr = s._intToListNode(465);

    assert(lr->val == 5);
    ListNode * r2 = lr->next;
    assert(r2->val == 6);
    ListNode* r3 = r2->next;
    assert(r3->val == 4);

    assert(s._listNodeToInt(lr) == 465);


    assert(s._listNodeToInt(s.addTwoNumbers(ll, lr)) == 807);

    // this input fails on leetcode as it is outside of int max
    // l1 [9]
    // l2 [1,9,9,9,9,9,9,9,9,9]



    // ListNode l1, l2;


    // 342
    // ListNode l1_1 = ListNode(3);
    // ListNode l1_2 = ListNode(4, &l1_1);
    // l1 = ListNode(2, &l1_2);

    // 465
    // ListNode l2_1 = ListNode(4);
    // ListNode l2_2 = ListNode(6, &l2_1);
    // l1 = ListNode(5, &l2_2);





    // l1 = 0 and l2 = 0
    
    // l1 nullptr and l2 nullptr
    
    // l1 or l2 nullptr


    return 0;
}
