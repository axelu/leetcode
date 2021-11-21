
// 430. Flatten a Multilevel Doubly Linked List
// https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/




/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head) {
        if( head == nullptr ) return head;

        Node* node = head;
        stack<Node*> stck;
        while(node != nullptr ) {
            if( node->child != nullptr ) {
                if( node->next != nullptr ) stck.push(node->next);
                node->next = node->child;
                node->child = nullptr;
                node->next->prev = node;
                node = node->next;
                continue;
            }
            if( node->next != nullptr ) {
                node = node->next;
                continue;
            }
            if( !stck.empty() ) {
                node->next = stck.top();
                stck.pop();
                node->next->prev = node;
            }
            node = node->next;
        }
        return head;
    }
};
