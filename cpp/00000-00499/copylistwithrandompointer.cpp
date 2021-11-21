
// 138. Copy List with Random Pointer
// https://leetcode.com/problems/copy-list-with-random-pointer/



/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
private:
    unordered_map<Node*,Node*> um;

    Node* cloneNode(Node* node) {
        Node* clone;
        auto f = um.find(node);
        if( f == um.end() ) {
            clone = new Node(node->val);
            um.insert({node,clone});
        } else {
            clone = f->second;
        }
        return clone;
    }
public:
    Node* copyRandomList(Node* head) {
        if( head == nullptr ) return nullptr;

        Node* clone;
        Node* randomClone;
        Node* randomNextClone;
        Node* prev = nullptr;
        Node* curr = head;
        while( curr != nullptr ) {
            // current node
            clone = cloneNode(curr);
            if( prev != nullptr )
                prev->next = clone;

            // current node's random
            if( curr->random != nullptr ) {
                randomClone = cloneNode(curr->random);
                clone->random = randomClone;
                // random next
                if( curr->random->next != nullptr ) {
                    randomNextClone = cloneNode(curr->random->next);
                    clone->random->next = randomNextClone;
                }
            }

            curr = curr->next;
            prev = clone;
        }

        return um.find(head)->second;
    }
};
