
// 3157. Find the Level of Tree with Minimum Sum
// https://leetcode.com/problems/find-the-level-of-tree-with-minimum-sum/




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
    long sum[100000]; // sum[i] is sum of all nodes at level i, we have max 100000 levels

    void dfs(TreeNode* root, int level) {
        if( root == nullptr )
            return;

        sum[level] += (long)(root->val);
        dfs(root->left, level + 1);
        dfs(root->right, level + 1);

        return;
    }
public:
    int minimumLevel(TreeNode* root) {
        memset(sum,0,sizeof sum);

        dfs(root, 0);

        // 1 <= Node.val <= 1e9
        // hence if sum at a given value from bottom up is 0, then the tree has not nodes on that level

        long mn = LONG_MAX;
        int ans;

        for(int i = 99999; i >= 0; --i) {
            if( sum[i] == 0L )
                continue;

            if( sum[i] <= mn ) {
                mn = sum[i];
                ans = i;
            }
        }

        return ans + 1; // levels are 1 indexed
    }
};
