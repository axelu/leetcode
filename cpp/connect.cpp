
// 116. Populating Next Right Pointers in Each Node
// day 13 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/565/week-2-november-8th-november-14th/3529/
// https://leetcode.com/problems/populating-next-right-pointers-in-each-node/


/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if( root == nullptr ) return root;

        // BFS

        queue<pair<int,Node*>> q; // height,node
        q.push({0,root});

        Node* lft;
        int p = -1;
        while( !q.empty() ) {
            auto [h,n] = q.front();
            q.pop();
            if( h != p )
                p = h;
            else
                lft->next = n;
            lft = n;
            if( n->left != nullptr ) { // perfect binary tree: if left child, then also right child
                q.push({h+1,n->left});
                q.push({h+1,n->right});
            }
        }
       return root;
    }
};
