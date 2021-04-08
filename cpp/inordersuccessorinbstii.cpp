
// 510. Inorder Successor in BST II
// https://leetcode.com/problems/inorder-successor-in-bst-ii/




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
    Node* inorderTraversal(Node* root) {
        if( root == nullptr ) return nullptr;

        Node* res = inorderTraversal(root->left);
        return res != nullptr ? res : root;
    }

public:
    Node* inorderSuccessor(Node* node) {

        // if we have a right child, the answer is the 1st element of an
        // inorder traversal starting at the right child
        if( node->right != nullptr ) return inorderTraversal(node->right);

        // we will go up the tree till we are the left child of a parent.
        // that parent is the answer.

        Node* ans = nullptr;
        while( node->parent != nullptr ) {
            if( node->parent->left == node ) {
                ans = node->parent;
                break;
            }
            node = node->parent;
        }
        return ans;
    }
};
