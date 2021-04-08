
// 222. Count Complete Tree Nodes
// https://leetcode.com/problems/count-complete-tree-nodes/

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
    int computeDepth(TreeNode* root) {
        int depth = 0;
        while(nullptr != root->left) {
            root = root->left;
            ++depth;
        }
        return depth;
    }

    bool search(int idx, int& depth, TreeNode* root) {
        int left = 0;
        int right = (int)pow(2,depth) - 1;
        int pivot;
        for(int i = 0; i < depth; ++i) {
            pivot = left + (right - left) / 2;
            if( idx <= pivot ) {
                root = root->left;
                right = pivot;
            } else {
                root = root->right;
                left = pivot + 1;
            }
        }
        return nullptr != root;
    }

public:
    int countNodes(TreeNode* root) {
        if( nullptr == root ) return 0;
        int depth = computeDepth(root);
        if( 0 == depth ) return 1;

        // last level nodes are indexed 0 to 2**d - 1 (left -> right).
        // binary search to check how many nodes exist
        int left = 1;
        int right = (int)pow(2,depth) - 1;
        int pivot;
        while(left <= right) {
            pivot = left + (right - left) / 2;
            if( search(pivot,depth,root) ) left = pivot + 1;
            else right = pivot - 1;
        }

        // tree contains 2**d - 1 nodes on the first (d - 1) levels
        // and left nodes on the last level.
        return (int)pow(2,depth) - 1 + left;

    }
};
