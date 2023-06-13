
// 2476. Closest Nodes Queries in a Binary Search Tree
// https://leetcode.com/problems/closest-nodes-queries-in-a-binary-search-tree/




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
    int q_sz;
    vector<vector<int>> qwidx;
    vector<vector<int>> ans;

    void dfs(TreeNode* root, int& i, int x, int y) {
        // go right: x: record largest one smaller than target
        // go left:  y: record smallest one larger than target

        if( root == nullptr ) {
            ans[qwidx[i][1]] = {x,y};
            ++i;
            return;
        }

        while( i < q_sz ) {

            int k = qwidx[i][0];

            if( root->val == k ) {
                ans[qwidx[i][1]] = {k,k};
                ++i;

            } else if( root->val > k ) {
                // go left
                dfs(root->left,i,x,root->val);

            } else { // root->val < k
                // go up or right
                if( y != -1 && k >= y )
                    return;
                dfs(root->right,i,root->val,y);
            }
        }

        return;
    }

public:
    vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
        q_sz = queries.size();

        qwidx.assign(q_sz,vector<int>(2));
        for(int i = 0; i < q_sz; ++i)
            qwidx[i] = {queries[i],i};
        sort(qwidx.begin(),qwidx.end());

        ans.assign(q_sz,vector<int>(2));

        int i = 0;
        dfs(root,i,-1,-1);

        return ans;
    }
};
