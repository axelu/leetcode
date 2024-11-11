
// 3294. Convert Doubly Linked List to Array II
// https://leetcode.com/problems/convert-doubly-linked-list-to-array-ii/




/**
 * Definition for doubly-linked list.
 * class Node {
 *     int val;
 *     Node* prev;
 *     Node* next;
 *     Node() : val(0), next(nullptr), prev(nullptr) {}
 *     Node(int x) : val(x), next(nullptr), prev(nullptr) {}
 *     Node(int x, Node *prev, Node *next) : val(x), next(next), prev(prev) {}
 * };
 */
class Solution {
public:
	vector<int> toArray(Node *node){

        // get head
        Node *head = nullptr;
        while( head == nullptr ) {
            if( node->prev == nullptr ) {
                head = node;
            } else {
                node = node->prev;
            }
        }

        vector<int> ans;
        Node* nd = head;
        while( nd != nullptr ) {
            ans.push_back(nd->val);
            nd = nd->next;
        }

        return ans;
    }
};
