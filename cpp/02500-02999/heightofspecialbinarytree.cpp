
// 2773. Height of Special Binary Tree
// https://leetcode.com/problems/height-of-special-binary-tree/



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
    int dfs(TreeNode* tn) {
        // I am a leave if
        //   I have no children OR
        //   I have a right child who's left child is me

        if( (tn->left == nullptr && tn->right == nullptr) ||
            ( tn->right != nullptr && tn->right->left == tn ) )
            return 0;

        int ret = 0;
        if( tn->left != nullptr )
            ret = 1 + dfs(tn->left);
        if( tn->right != nullptr )
            ret = max(ret, 1 + dfs(tn->right));

        return ret;
    }
public:
    int heightOfTree(TreeNode* root) {

        // let k be the number of leafes in the binary tree rooted in root
        // left child   i >  k:  bi-1
        //              i <= k:  bk
        // right child  i <  k:  bi+1
        //              i >= k:  b1
        // said differently:
        //   if I have a right child who's left child is me, I am a leaf!




        return dfs(root);
    }
};
