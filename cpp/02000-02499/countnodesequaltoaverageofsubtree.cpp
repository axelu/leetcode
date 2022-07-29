
// 2265. Count Nodes Equal to Average of Subtree
// https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/



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
    int ans;

    pair<int,int> dfs(TreeNode* tn) {
        // return sum and count of nodes in subtree of tn

        if( tn == nullptr )
            return {0,0};

        // left
        auto [sl,cl] = dfs(tn->left);

        // right
        auto [sr,cr] = dfs(tn->right);

        int sum = sl + sr + tn->val;
        int cnt = cl + cr + 1;

        if( floor((float)sum/(float)cnt) == tn->val )
            ++ans;

        return {sum,cnt};
    }
public:
    int averageOfSubtree(TreeNode* root) {
        ans = 0;
        dfs(root);
        return ans;
    }
};
