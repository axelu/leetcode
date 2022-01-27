
// 968. Binary Tree Cameras
// https://leetcode.com/problems/binary-tree-cameras/
// day 16 May 2021 challenge
// https://leetcode.com/explore/featured/card/may-leetcoding-challenge-2021/600/week-3-may-15th-may-21st/3745/




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
    // call recursive, parent calling child and teling it:
    // a) parent to child: I am monitoring you OR
    // b) parent to child: I am not monitoring you
    // in case b) child either needs to monitor itself, in which case it can
    //            it can also monitor it children OR
    //            its children need to monitor it
    // issue is when we are two levels removed
    // camera -> nocamera ->nocamera -> camera; this is ok!
    // a leaf node cannot be monitored by its children, only byitself or its parent
    // each node has a choice to have a camera or not
    // we cannot have more then 3 depth steps w/o a camera

    int mem[1001][2][2];
    int id;

    int dfs(TreeNode* root, bool parentHasCamera, bool installCamera) {
        // won't be called for root == nullptr

        if( root->val == 0 ) root->val = ++id;

        // leaf node
        if( root->left == nullptr && root->right == nullptr ) {
            // it does not matter if we are asked to install a camera or not
            // if our parent does NOT have one, we need to install one
            // if we are asked to install one, we will disobey as it is not needed
            return parentHasCamera ? 0 : 1;
        }

        if( mem[root->val][parentHasCamera][installCamera] != -1 )
            return mem[root->val][parentHasCamera][installCamera];

        int ret;

        // node has at least one child
        if( !parentHasCamera && !installCamera ) {
            // we need to make sure that at least one of our children installs a camera
            if( root->left != nullptr && root->right != nullptr ) {
                // left and right child
                int lwith    = dfs(root->left, false,true );
                int lwithout = dfs(root->left, false,false);
                int rwith    = dfs(root->right,false,true );
                int rwithout = dfs(root->right,false,false);
                ret = min({lwith+rwithout,lwithout+rwith,lwith+rwith});
            } else if( root->left != nullptr ) {
                // left child only
                ret = dfs(root->left, false,true );
            } else {
                // right child only
                ret = dfs(root->right,false,true );
            }
        } else if( installCamera ) {
            // it doesn't matter if the parent has one or not, we will install one
            int lwith = 0;
            if( root->left != nullptr ) lwith     = dfs(root->left, true,true );
            int lwithout = 0;
            if( root->left != nullptr ) lwithout  = dfs(root->left, true,false);
            int rwith = 0;
            if( root->right != nullptr ) rwith    = dfs(root->right,true,true );
            int rwithout = 0;
            if( root->right != nullptr ) rwithout = dfs(root->right,true,false);

            ret = 1 + min({lwith+rwith,lwith+rwithout,lwithout+rwith,lwithout+rwithout});
        } else {
            int lwith = 0;
            if( root->left != nullptr ) lwith     = dfs(root->left,false,true );
            int lwithout = 0;
            if( root->left != nullptr ) lwithout  = dfs(root->left,false,false);
            int rwith = 0;
            if( root->right != nullptr ) rwith    = dfs(root->right,false,true );
            int rwithout = 0;
            if( root->right != nullptr ) rwithout = dfs(root->right,false,false);

            ret = min({lwith+rwith,lwith+rwithout,lwithout+rwith,lwithout+rwithout});
        }

        return mem[root->val][parentHasCamera][installCamera] = ret;
    }


public:
    int minCameraCover(TreeNode* root) {
        // number of nodes in the given tree will be in the range [1,1000]
        // every node has value 0

        memset(mem,-1,sizeof mem);
        id = 0;

        return min(dfs(root,false,true),dfs(root,false,false));
    }
};
