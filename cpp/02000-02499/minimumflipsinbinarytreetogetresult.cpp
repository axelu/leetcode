
// 2313. Minimum Flips in Binary Tree to Get Result
// https://leetcode.com/problems/minimum-flips-in-binary-tree-to-get-result/


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
    unordered_map<TreeNode*,pair<int,int>> mem; // treenode, {false,true) result

    int dfs(TreeNode* tn, bool result) {
        // result is the result we need to return

        if( tn->val == 0 || tn->val == 1 )      // we are at a leaf
            return tn->val == result ? 0 : 1;

        auto f = mem.find(tn);
        if( f == mem.end() ) {
            f = mem.insert({tn,{-1,-1}}).first;
        } else {
            if( result && f->second.second != -1 )
                return f->second.second;
            if( !result & f->second.first != -1 )
                return f->second.first;
        }

        int ret = 0;

        if( tn->val == 2 ) {                    // OR
            if( result ) {
                int l0 = dfs(tn->left,false);
                int l1 = dfs(tn->left,true);
                int r0 = dfs(tn->right,false);
                int r1 = dfs(tn->right,true);
                ret = min({l0+r1,l1+r0,l1+r1});
            } else {
                ret = dfs(tn->left,false) + dfs(tn->right,false);
            }

        } else if( tn->val == 3 ) {             // AND
            if( result ) {
                ret = dfs(tn->left,true) + dfs(tn->right,true);
            } else {
                int l0 = dfs(tn->left,false);
                int l1 = dfs(tn->left,true);
                int r0 = dfs(tn->right,false);
                int r1 = dfs(tn->right,true);
                ret = min({l0+r1,l1+r0,l0+r0});
            }

        } else if( tn->val == 4 ) {             // XOR
            int l0 = dfs(tn->left,false);
            int l1 = dfs(tn->left,true);
            int r0 = dfs(tn->right,false);
            int r1 = dfs(tn->right,true);
            if( result ) {
                ret = min(l0+r1,l1+r0);
            } else {
                ret = min(l0+r0,l1+r1);
            }

        } else {                                // NOT
            // we have either a right or a left child
            // that child will need to give us opposite of result
            ret = tn->left != nullptr ? dfs(tn->left,!result) : dfs(tn->right,!result);
        }

        if( result )
            f->second.second = ret;
        else
            f->second.first = ret;

        return ret;
    }
public:
    int minimumFlips(TreeNode* root, bool result) {

        return dfs(root,result);
    }
};
