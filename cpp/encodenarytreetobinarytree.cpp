
// 431. Encode N-ary Tree to Binary Tree
// https://leetcode.com/problems/encode-n-ary-tree-to-binary-tree/





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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Codec {
private:
    TreeNode* addRightChild(TreeNode* troot, int val) {
        troot->right = new TreeNode(val);
        return troot->right;
    }

    TreeNode* encode(Node* root, TreeNode* troot) {
        int n = root->children.size();
        // process 1st child
        TreeNode* p;
        if( n >= 1 ) {
            p = new TreeNode(root->children[0]->val);
            troot->left = p;
        }
        // process remaining children
        for(int i = 1; i < n; ++i) {
            p = addRightChild(p,root->children[i]->val);
        }
        return troot->left;
    }
public:
    // Encodes an n-ary tree to a binary tree.
    TreeNode* encode(Node* root) {
        if( root == nullptr ) return nullptr;

        // BFS
        queue<pair<Node*,TreeNode*>> q;
        pair<Node*,TreeNode*> qe;
        Node* currNode;
        TreeNode* currTreeNode;
        TreeNode* troot = new TreeNode(root->val);
        q.push({root,troot});
        TreeNode* t;
        while( !q.empty() ) {
            qe = q.front();
            q.pop();
            currNode = qe.first;
            currTreeNode = qe.second;
            // process 1st child
            int n = currNode->children.size();
            if( n >= 1 ) {
                t = encode(currNode,currTreeNode);
                q.push({currNode->children[0],t});
            }
            // process remaining children
            for(int i = 1; i < n; ++i) {
                t = t->right;
                q.push({currNode->children[i],t});
            }
        }
        return troot;
    }

    // Decodes your binary tree to an n-ary tree.
    Node* decode(TreeNode* root) {
        if( root == nullptr ) return nullptr;

        // BFS
        queue<pair<Node*,TreeNode*>> q;
        pair<Node*,TreeNode*> qe;
        Node* currNode;
        TreeNode* currTreeNode;
        Node* nroot = new Node(root->val);
        q.push({nroot,root});
        Node* node;
        TreeNode* t;
        while( !q.empty() ) {
            qe = q.front();
            q.pop();
            currNode = qe.first;
            currTreeNode = qe.second;
            t = nullptr;
            // process 1st child
            if( currTreeNode->left != nullptr ) {
                t = currTreeNode->left;
                node = new Node(t->val);
                currNode->children.push_back(node);
                q.push({node,t});
            }
            // process remaining children
            if( t != nullptr )
                while( t->right != nullptr ) {
                    t = t->right;
                    node = new Node(t->val);
                    currNode->children.push_back(node);
                    q.push({node,t});
                }
        }
        return nroot;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(root));
