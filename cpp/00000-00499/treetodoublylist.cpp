
// 426. Convert Binary Search Tree to Sorted Doubly Linked List
// https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/



/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if( root == nullptr ) return nullptr;

        auto cmp = [](Node* l, Node* r) {
            return l->val > r->val;
        };
        priority_queue<Node*, vector<Node*>, decltype(cmp)> pq(cmp); // min heap

        // BFS
        queue<Node*> q;
        q.push(root);
        Node* qe;
        while(!q.empty()) {
            qe = q.front();
            q.pop();
            pq.push(qe);
            if( qe->left != nullptr ) q.push(qe->left);
            if( qe->right != nullptr ) q.push(qe->right);
        }

        Node* ans = nullptr;
        Node* prev = nullptr;
        Node* pqe;

        // first element
        if( !pq.empty() ) {
            pqe = pq.top();
            pq.pop();
            prev = pqe;
            // set the root of our return list
            ans = pqe;
        }

        while( !pq.empty() ) {
            pqe = pq.top();
            pq.pop();
            prev->right = pqe; // successor
            pqe->left = prev;  // predecessor
            prev = pqe;
        }

        // link last element and first element
        if( prev != nullptr ) prev->right = ans;
        if( ans != nullptr ) ans->left = prev;

        return ans;
    }
};
