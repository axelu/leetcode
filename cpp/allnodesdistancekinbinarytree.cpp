
// 863. All Nodes Distance K in Binary Tree
// https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/




/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:

    int dfs(TreeNode* root, TreeNode* target, int k, int step, vector<int>& ans) {
        // if step = -1 then the target node has not been found yet

        if( root == nullptr ) return -1;

        if( step != -1 ) {
            // an ancestor discovered the target already
            if( step == k ) {
                ans.push_back(root->val);
            } else {
                dfs(root->left,target,k,step+1,ans);
                dfs(root->right,target,k,step+1,ans);
            }
            return -1;

        } else {
            // target still to be discovered

            // am I the target?
            if( root == target ) {
                if( k == 0 ) {
                    ans.push_back(root->val);
                    return -1;
                } else {
                    dfs(root->left,target,k,1,ans);
                    dfs(root->right,target,k,1,ans);
                    return 1;
                }

            } else {

                // left
                int t = dfs(root->left,target,k,-1,ans);
                if( t != -1 ) {
                    // my left child discovered the target within less than k steps
                    if( t == k ) {
                        ans.push_back(root->val);
                        return -1;
                    }
                    // call my right child with the remaining steps
                    dfs(root->right,target,k,t+1,ans);
                    // return the remaining steps
                    return t+1;
                }

                // the target may have been discovered in my left subtree
                if( !ans.empty() )
                    return -1;

                // right
                t = dfs(root->right,target,k,-1,ans);
                if( t != -1 ) {
                    // my right child discovered the target within less than k steps
                    if( t == k ) {
                        ans.push_back(root->val);
                        return -1;
                    }
                    // call my left child with the remaining steps
                    dfs(root->left,target,k,t+1,ans);
                    // return the remaining steps
                    return t+1;
                }

                return -1;
            }
        }
    }


public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int> ans;
        dfs(root,target,k,-1,ans);
        return ans;
    }
};
