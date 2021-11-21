#include <iostream>
#include <cassert>

#include <vector>

using namespace std;

// 21. Merge Two Sorted Lists
// https://leetcode.com/problems/merge-two-sorted-lists/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {

        if ( l1 == nullptr ) return l2;
        if ( l2 == nullptr ) return l1;

        /* this works
         * ****************************************************************
        ListNode* ln = new ListNode();
        if ( l1->val < l2->val ) {
            ln->val = l1->val;
            ln->next = mergeTwoLists(l1->next, l2);
        } else {
            ln->val = l2->val;
            ln->next = mergeTwoLists(l1, l2->next);
        }
        
        return ln;
         * ****************************************************************
         */


        /* this also works
         * ****************************************************************
        vector<ListNode*> v;
        
        while ( l1 != nullptr && l2 != nullptr ) {
            if ( l1->val < l2->val ) {
                if( !v.empty() ) v.back()->next = l1;
                v.push_back(l1);
                l1 = l1->next;
            } else {
                if( !v.empty() ) v.back()->next = l2;
                v.push_back(l2);
                l2 = l2->next;
            }
        }

        // for(auto it = v.begin(); it != v.end(); ++it) {
        //     if ( it + 1 != v.end() ) {
        //         (*it)->next = *(it+1);
        //     }
        // }

        if ( l1 != nullptr ) {
            (*(v.end() - 1))->next = l1;
        } else {
            (*(v.end() - 1))->next = l1;
        }


        return *v.begin();
         * ***************************************************************
         */

        ListNode* lr = ( l1->val < l2->val ) ? l1 : l2;
        ListNode* ln = nullptr;
        while ( l1 != nullptr && l2 != nullptr ) {
            if ( l1->val < l2->val ) {
                if( ln != nullptr ) ln->next = l1;
                ln = l1;
                l1 = l1->next;
            } else {
                if( ln != nullptr ) ln->next = l2;
                ln = l2;
                l2 = l2->next;
            }
        }
        ln->next = ( l1 != nullptr) ? l1 : l2;
        return lr;


/*
        ListNode* ln;
        ListNode* lr; // what we will return
        if ( l1->val < l2->val ) {
            lr = l1;
            l1 = l1->next;
        } else {
            lr = l2;
            l2 = l2->next;
        }
        lr->next = ln;

        while ( l1 != nullptr && l2 != nullptr ) {
            if ( l1->val < l2->val ) {
                ln = l1;

            } else {
                ListNode* t = l2->next;
                l2->next = l1;


            }

        }

        // TODO add where we stopped


        return ln;
*/
/*        
        if ( l1->val < l2->val ) {
            ListNode* t = l1->next;
            l1->next = l2;
            l2->next = mergeTwoLists(t, l2);
            return l1;
        } else {
            ListNode* t = l2->next;
            l2->next = l1;
            l1->next = mergeTwoLists(t, l1);
            return l2;
        }
*/
    }
private:
    ListNode* _mergeTwoLists(ListNode* l1, ListNode* l2) {

        if ( l1 == nullptr ) return l2;
        if ( l2 == nullptr ) return l1;

        return ( l1->val < l2->val ) ? l1 : l2;

    }
};

int main() {

    Solution s;
/*
    ListNode* l16 = new ListNode(10);
    ListNode* l15 = new ListNode(7, l16);
    ListNode* l14 = new ListNode(6, l15);
    ListNode* l13 = new ListNode(4, l14);
    ListNode* l12 = new ListNode(2, l13);
    ListNode* l11 = new ListNode(1, l12);
    ListNode* l23 = new ListNode(4);
    ListNode* l22 = new ListNode(3, l23);
    ListNode* l21 = new ListNode(1, l22);
*/

    ListNode* l16 = new ListNode(8);
    ListNode* l15 = new ListNode(6, l16);
    ListNode* l14 = new ListNode(5, l15);
    ListNode* l13 = new ListNode(4, l14);
    ListNode* l12 = new ListNode(2, l13);
    ListNode* l11 = new ListNode(1, l12);
    ListNode* l23 = new ListNode(7);
    ListNode* l22 = new ListNode(3, l23);
    ListNode* l21 = new ListNode(1, l22);

    ListNode* ln1 = s.mergeTwoLists(l11, l21);

    while ( ln1 != nullptr ) {
        cout << ln1->val << endl;
        ln1 = ln1->next;
    }






    return 0;
}
