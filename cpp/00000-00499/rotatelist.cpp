
// 61. Rotate List
// day 7 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/559/week-1-october-1st-october-7th/3486/
// https://leetcode.com/problems/rotate-list/



#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <iterator>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <map>
#include <cmath>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
private:
    int n;
    vector<ListNode*> v;
    ListNode* _walk(ListNode* head, int l, int k) {
        if( head == nullptr ) return nullptr;

        if( l > n ) n = l;

        cout << "in " << head->val << " l " << l << " n " << n << endl;

        _walk(head->next,l + 1,k);

        cout << "af " << head->val << " l " << l << " n " << n << endl;
        if( k == n )
            return head;

        if( k > n )
            k = k % n;

        if( k == 0 )
            return head;

        if( l == n - k )
            head->next = nullptr;

        if( l > n - k )
            v.push_back(head);

        return head;
    }
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if( k == 0 ) return head;
        if( head == nullptr ) return head;
        if( head->next == nullptr ) return head;

        n = 0;
        ListNode* ln = _walk(head,1,k);

        if( v.empty() ) return head;
        for(auto nd : v) {
            nd->next = ln;
            ln = nd;
        }

        return ln;
    }
};

int main() {

    // chrono::time_point<chrono::system_clock> start;
    // chrono::time_point<chrono::system_clock> end;
    // chrono::duration<double> elapsed_seconds;

    // start = chrono::system_clock::now();
    // do something
    // end = chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    Solution s;

    // [0,1,2,3,4]
    ListNode* l1 = new ListNode(4);
    ListNode* l2 = new ListNode(3,l1);
    ListNode* l3 = new ListNode(2,l2);
    ListNode* l4 = new ListNode(1,l3);
    ListNode* l5 = new ListNode(0,l4);

    ListNode* r = l5;
    while( r != nullptr ) {
        cout << r->val << " ";
        r = r->next;
    }
    cout << endl;
    r = s.rotateRight(l5,12);

    while( r != nullptr ) {
        cout << r->val << " ";
        r = r->next;
    }
    cout << endl;


    return 0;
}
