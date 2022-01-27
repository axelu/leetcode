
// 708. Insert into a Sorted Circular Linked List
// https://leetcode.com/problems/insert-into-a-sorted-circular-linked-list/





/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/

class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        if( head == nullptr ) {
            Node* nd = new Node(insertVal);
            nd->next = nd;
            return nd;
        }
        if( head->next == head ) {
            Node* nd = new Node(insertVal);
            nd->next = head;
            head->next = nd;
            return head;
        }

        // at the insertion point:
        // the node pointing to our new node has to be less or equal
        // the node that our new node points to is greater or equal

        Node* prev = head;
        Node* nd = head->next;
        while( nd != head ) {
            if( prev->val > nd->val && (insertVal > prev->val || insertVal < nd->val) )
                break;
            else if( prev->val <= insertVal && nd->val >= insertVal )
                break;
            prev = nd;
            nd = nd->next;
        }
        Node* t = new Node(insertVal);
        prev->next = t;
        t->next = nd;

        return head;
    }
};
