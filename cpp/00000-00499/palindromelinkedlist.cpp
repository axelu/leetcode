#include <iostream>
#include <cassert>

#include <vector>

// 234. Palindrome Linked List
// https://leetcode.com/problems/palindrome-linked-list/


using namespace std;


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
    bool isPalindrome(ListNode* head) {
        if ( head == nullptr ) return true;                                        
        if ( head->next == nullptr ) return true;                                  
                                                                                   
        vector<int> v;                                                             
        ListNode* cur = head;                                                      
        while( cur != nullptr ) {                                                 
            v.push_back(cur->val);                                                 
            cur = cur->next;                                                                               
        }
        int n = v.size();
        int l = 0, r = n-1;
        while(l<r) {
            if( v[l] != v[r] ) return false;
            ++l; --r;
        }        
                                                                                   
        return true;                                          
    }
};

int main() {

    Solution s;

    ListNode* l1 = new ListNode(1);
    ListNode* l2 = new ListNode(2,l1);
    assert(s.isPalindrome(l2) == false);
    ListNode* l3 = new ListNode(1,l2);
    assert(s.isPalindrome(l3) == true);
    ListNode* l4 = new ListNode(2,l2);
    ListNode* l5 = new ListNode(1,l4);
    assert(s.isPalindrome(l5) == true);



    return 0;
}
