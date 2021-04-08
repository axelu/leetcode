
// 1123. Lowest Common Ancestor of Deepest Leaves
// https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/

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

// https://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/
// https://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-tree-set-2-using-parent-pointer/
// https://www.geeksforgeeks.org/find-lca-in-binary-tree-using-rmq/

class Solution {
private:
    pair<TreeNode*,int> np[1000];
    int level[1000];
    int mxlvl;
    int idx;

    void dfs(TreeNode* root, int h, int parent) {
        if( root == nullptr ) return;

        np[idx] = make_pair(root,parent);
        level[idx] = h;
        if( h > mxlvl ) mxlvl = h;
        int currIdx = idx;
        ++idx;

        dfs(root->left,h+1,currIdx);
        dfs(root->right,h+1,currIdx);
    }

public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        // idea: find left most and right most node on max level
        //       then find those nodes' lowest common ancestor (LCA)

        mxlvl = 0;
        idx = 0;
        dfs(root,0,-1);

        // left most node at max depth
        pair<TreeNode*,int> l;
        for(int i = 0; i < idx; ++i)
            if( level[i] == mxlvl )
                l = np[i];
        // right most node at max depth
        pair<TreeNode*,int> r;
        for(int i = idx-1; i >= 0; --i)
            if( level[i] == mxlvl )
                r = np[i];

        // if one and the same we are done
        // otherwise follow up the parent pointers till same parent
        while( l.first != r.first ) {
            l = np[l.second];
            r = np[r.second];
        }

        return l.first;
    }
};
