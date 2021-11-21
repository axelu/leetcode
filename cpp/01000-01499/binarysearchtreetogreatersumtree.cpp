
// 1038. Binary Search Tree to Greater Sum Tree
// https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    void inorder(TreeNode* root, vector<int>& nodes) {
        if( nullptr == root ) return;

        // Inorder is sorted order for a BST
        inorder(root->left, nodes);
        nodes.push_back(root->val);
        inorder(root->right, nodes);
    }

    int bstToGst(TreeNode* root, vector<int>& nodes, int inorderIdx) {
        if( nullptr == root ) return inorderIdx;

        // Inorder is sorted order for a BST
        inorderIdx = bstToGst(root->left,nodes,inorderIdx);
        root->val = nodes[inorderIdx];
        return bstToGst(root->right,nodes,inorderIdx+1);
    }

public:
    TreeNode* bstToGst(TreeNode* root) {
        vector<int> nodes;
        inorder(root,nodes);

        for(int i = nodes.size()-2; i >= 0; --i)
            nodes[i] += nodes[i+1];
        bstToGst(root,nodes,0);
        return root;
    }
};
