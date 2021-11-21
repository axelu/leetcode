
// 1339. Maximum Product of Splitted Binary Tree
// https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/


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
public:
    int maxProduct(TreeNode* root) {
        _walk(root);

        // cout << "total      " << total << endl;
        // for(int i : sums) cout << i << " ";
        // cout << endl;

        int a;
        int f = total/2;
        auto it = lower_bound(sums.begin(), sums.end(), f);
        if( it == sums.begin() ) {
            a = *it;
        } else if( it == sums.end() ) {
            a = *sums.rbegin();
        } else {
            a = ( *it - f <= f - *prev(it) ) ? *it : *prev(it);
        }

        const unsigned int m = 1000000007; // Modulo 10^9+7 = 1000000007
        unsigned long long i = 1;
        i = (i * a) % m;
        i = (i * (total - a)) % m;

        return i;
    }
private:
    int total = 0;
    set<int> sums;
    int _walk(TreeNode* root) {
        if( root == nullptr ) return 0;

        // cout << "root->val " << root->val << endl;

        total += root->val;

        int l = _walk(root->left);
        int r = _walk(root->right);

        if( l > 0 ) sums.insert(l);
        if( r > 0 ) sums.insert(r);

        return root->val + l + r;
    }
};
