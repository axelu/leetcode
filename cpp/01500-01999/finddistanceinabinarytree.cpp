
// 1740. Find Distance in a Binary Tree
// https://leetcode.com/problems/find-distance-in-a-binary-tree/




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
    int dist(TreeNode* root, int key, int d) {
        if( nullptr == root )
            return -1;
        if( root->val == key )
            return d;

        int ans = dist(root->left,key,d+1);
        if( -1 != ans ) return ans;
        return dist(root->right,key,d+1);
    }

    TreeNode* LCA(TreeNode* root, int key1, int key2) {
        if( nullptr == root )
            return nullptr;

        if( root->val == key1 || root->val == key2 )
            return root;

        TreeNode* lft_lca = LCA(root->left,key1,key2);
        TreeNode* rgt_lca = LCA(root->right,key1,key2);

        // if both of the above calls return something other than nullptr,
        // then one key is present in one subtree and
        // other key is present in other subtree, hence the
        // current node is the Lowest Common Ancestor (LCA) to both keys
        if( nullptr != lft_lca && nullptr != rgt_lca )
            return root;

        // else check if left subtree or right subtree is LCA
        return nullptr != lft_lca ? lft_lca : rgt_lca;
    }

public:
    int findDistance(TreeNode* root, int p, int q) {
        // base case
        if( p == q ) return 0;

        TreeNode* lca = LCA(root,p,q);
        return dist(lca,p,0)+dist(lca,q,0);
    }
};
