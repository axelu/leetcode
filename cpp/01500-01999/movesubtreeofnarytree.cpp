
// 1516. Move Sub-Tree of N-Ary Tree
// https://leetcode.com/problems/move-sub-tree-of-n-ary-tree/




/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
private:
    Node* P;
    Node* Q;
    bool foundP,foundQ,case1;
    Node* pParent;
    Node* qParent;

    void dfs(Node* root, Node* parent, bool passedP, bool passedQ) {
        if( foundP && foundQ ) return;
        // am I P?
        if( root == P ) {
            pParent = parent;
            foundP  = true;
            passedP = true;
        }
        // am I Q?
        if( root == Q ) {
            qParent = parent;
            foundQ  = true;
            passedQ = true;
            if( passedP ) case1 = true;
        }
        if( foundP && foundQ ) return;
        for(int i = 0; i < root->children.size(); ++i)
            dfs(root->children[i],root,passedP,passedQ);
    }
public:
    Node* moveSubTree(Node* root, Node* p, Node* q) {
        // goal:   p to become a direct child of q.
        // case 1: Node q is in the sub-tree of node p.
        // case 2: Node p is in the sub-tree of node q.
        // case 3: Neither node p is in the sub-tree of node q nor node q is in the sub-tree of node p.

        // base case: p already a direct child of q
        for(int i = 0; i < q->children.size(); ++i)
            if( q->children[i] == p ) return root;

        P = p;
        Q = q;
        foundP = false;
        foundQ = false;
        case1 = false;
        dfs(root,nullptr,false,false);

        if( !case1 ) {
            // disconnect p from its current parent
            int i = 0;
            for(; i < pParent->children.size(); ++i)
                if( pParent->children[i] == p ) break;
            pParent->children.erase(pParent->children.begin()+i);
            // add p as the last child of q
            q->children.push_back(p);
            return root;
        }

        // case 1: Node q is in the sub-tree of node p.
        // disconnect q from its current parent
        int i = 0;
        for(; i < qParent->children.size(); ++i)
            if( qParent->children[i] == q ) break;
        qParent->children.erase(qParent->children.begin()+i);
        // disconnect p from its current parent
        vector<Node*>::iterator r;
        if( pParent != nullptr ) {
            i = 0;
            for(; i < pParent->children.size(); ++i)
                if( pParent->children[i] == p ) break;
            r = pParent->children.erase(pParent->children.begin()+i);
        }
        // add p as the last child of q
        q->children.push_back(p);
        // reconnect q to p's parent
        if( pParent != nullptr ) {
            pParent->children.insert(r,q);
        } else {
            root = q;
        }

        return root;
    }
};
