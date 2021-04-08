
// 1666. Change the Root of a Binary Tree
// https://leetcode.com/problems/change-the-root-of-a-binary-tree/



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

    void up(Node* cur, Node* newParent) {
        Node* curParent = cur->parent;
        cur->parent = newParent;
        if( nullptr == curParent ) return;

        if( curParent->left == cur ) curParent->left = nullptr;
        else curParent->right = nullptr;

        if( nullptr != cur->left ) cur->right = cur->left;
        cur->left = curParent;

        up(curParent,cur);
    }

public:
    Node* flipBinaryTree(Node* root, Node * leaf) {
        up(leaf,nullptr);
        return leaf;
    }
};
