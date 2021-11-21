#include <iostream>
#include <regex>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

// 143. Reorder List
// https://leetcode.com/problems/reorder-list/
// day 20 August 2020 challenge
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/551/week-3-august-15th-august-21st/3430/


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
    void reorderList(ListNode* head) {
        if( head == nullptr ) return;
        if( head->next == nullptr ) return;
        
        vector<ListNode*> t;
        _walk(head, t);
        if( t.size() == 2) return;
        
        auto itf = t.begin();
        auto itb = t.rbegin();
        while( true ) {
            (*itf)->next = *itb;
            ++itf;
            if(itb.base() - 1 - itf == 0) {
              (*itf)->next = nullptr;
              break;
            }
            (*itb)->next = *itf;
            ++itb;
            if(itb.base() - 1 - itf == 0) {
              (*itb)->next = nullptr;
              break;
            }
        }
    }
private:
    void _walk(ListNode* head, vector<ListNode*>& t) {
        if(head == nullptr) return;
        t.push_back(head);
        _walk(head->next, t);
    }
};

int main() {

  Solution s;

  ListNode* ln5 = new ListNode(5);
  ListNode* ln4 = new ListNode(4,ln5);
  ListNode* ln3 = new ListNode(3,ln4);
  ListNode* ln2 = new ListNode(2,ln3);
  ListNode* ln1 = new ListNode(1,ln2); // head

  s.reorderList(ln1);

  ListNode* lw = ln1;
  while (lw != nullptr) {
    cout << lw->val << " ";
    lw = lw->next;
  }
  cout << endl;









  return 0;
}
