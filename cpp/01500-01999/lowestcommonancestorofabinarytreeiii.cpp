
// 1650. Lowest Common Ancestor of a Binary Tree III
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii/



/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

class Solution {
private:

    bool search(Node* root, Node* target) {
        if( root == nullptr ) return false;
        if( root == target ) return true;

        if( search(root->left,target) ) return true;
        return search(root->right,target);
    }



public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        // is q a descendent of p? then p is LCA
        if( search(p,q) ) return p;
        // is p a descendent of q? then q is LCA
        if( search(q,p) ) return q;

        // walk to root starting either at p or q, we pick p
        unordered_set<Node*> us;
        while(p->parent != nullptr) {
            us.insert(p->parent);
            p = p->parent;
        }
        // walk to root starting at the other node, if same parent, we are done
        while(true) {
            if( us.find(q->parent) != us.end() ) return q->parent;
            q = q->parent;
        }
        return nullptr;
    }
};
