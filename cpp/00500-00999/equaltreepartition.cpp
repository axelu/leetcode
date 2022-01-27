
// 663. Equal Tree Partition
// https://leetcode.com/problems/equal-tree-partition/





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
    // augmented TreeNode
    struct TreeNodeAug {
        int val;
        int sum;
        TreeNodeAug *left;
        TreeNodeAug *right;
        TreeNodeAug(int x) : val(x), sum(0), left(nullptr), right(nullptr) {}
    };

    TreeNodeAug* dfs(TreeNode* root) {
        if( root == nullptr ) return nullptr;

        TreeNodeAug* tna = new TreeNodeAug(root->val);
        tna->left  = dfs(root->left);
        tna->right = dfs(root->right);

        int sum = root->val;
        sum += tna->left  != nullptr ? tna->left->sum  : 0;
        sum += tna->right != nullptr ? tna->right->sum : 0;
        tna->sum = sum;

        return tna;
    }

    bool dfs(TreeNodeAug* root, int top) {
        if( root == nullptr ) return false;

        int lsum = root->left  != nullptr ? root->left->sum  : 0;
        int rsum = root->right != nullptr ? root->right->sum : 0;

        int total;
        // can we sever the left connection?
        if( root->left  != nullptr ) {
            total = rsum + root->val + top;
            if( total == lsum ) return true;
        }
        // can we sever the right connection?
        if( root->right  != nullptr ) {
            total = lsum + root->val + top;
            if( total == rsum ) return true;
        }

        if( dfs(root->left,rsum+root->val+top) ) return true;
        return dfs(root->right,lsum+root->val+top);
    }

public:
    bool checkEqualTree(TreeNode* root) {
        TreeNodeAug* tnaRoot = dfs(root);
        return dfs(tnaRoot,0);
    }
};
