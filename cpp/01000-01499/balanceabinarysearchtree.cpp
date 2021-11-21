
// 1382. Balance a Binary Search Tree
// https://leetcode.com/problems/balance-a-binary-search-tree/


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
    void inorder(TreeNode* root, vector<TreeNode*>& nodes) {
        if( nullptr == root ) return;

        // Inorder is sorted order for a BST
        inorder(root->left, nodes);
        nodes.push_back(root);
        inorder(root->right, nodes);
    }

    TreeNode* buildTree(vector<TreeNode*>& nodes, int start, int end) {
        // recursive function to build a balanced BST from a sorted array
        if( start > end ) return nullptr;

        int mid = (start + end)/2;
        TreeNode *root = nodes[mid];

        // using index in Inorder traversal, build left and right subtress
        root->left  = buildTree(nodes,start,mid-1);
        root->right = buildTree(nodes,mid+1,end);

        return root;
    }
public:
    TreeNode* balanceBST(TreeNode* root) {
        // build a sorted array nodes via inorder traversal
        vector<TreeNode*> nodes;
        inorder(root, nodes);

        // build balanced BST from sorted array of nodes
        return buildTree(nodes,0,nodes.size()-1);
    }
};
