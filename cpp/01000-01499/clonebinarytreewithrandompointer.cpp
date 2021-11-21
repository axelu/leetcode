
// 1485. Clone Binary Tree With Random Pointer
// https://leetcode.com/problems/clone-binary-tree-with-random-pointer/


/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     Node *left;
 *     Node *right;
 *     Node *random;
 *     Node() : val(0), left(nullptr), right(nullptr), random(nullptr) {}
 *     Node(int x) : val(x), left(nullptr), right(nullptr), random(nullptr) {}
 *     Node(int x, Node *left, Node *right, Node *random) : val(x), left(left), right(right), random(random) {}
 * };
 */

class Solution {
private:
    void clone1(Node* root, unordered_map<Node*,NodeCopy*>& um) {
        if( root == nullptr ) return;
        um.insert({root,new NodeCopy(root->val)});
        clone1(root->left,um);
        clone1(root->right,um);
    }

    void clone2(Node* root, unordered_map<Node*,NodeCopy*>& um) {
        NodeCopy* rootClone = um.find(root)->second;
        NodeCopy* clone;

        // random
        if( root->random != nullptr ) {
            clone = um.find(root->random)->second;
            rootClone->random = clone;
        }
        // left
        if( root->left != nullptr ) {
            clone = um.find(root->left)->second;
            rootClone->left = clone;
            clone2(root->left,um);
        }
         // right
        if( root->right != nullptr ) {
            clone = um.find(root->right)->second;
            rootClone->right = clone;
            clone2(root->right,um);
        }
    }


public:
    NodeCopy* copyRandomBinaryTree(Node* root) {
        if( root == nullptr ) return nullptr;
        unordered_map<Node*,NodeCopy*> um;
        clone1(root,um);
        clone2(root,um);
        return um.find(root)->second;
    }
};
