
// 1609. Even Odd Tree
// https://leetcode.com/contest/weekly-contest-209/problems/even-odd-tree/
// https://leetcode.com/problems/even-odd-tree/



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
    int m[100000];
    bool r;
    void _walk(TreeNode* root, int l) {
        if( r == false ) return;
        if( root == nullptr ) return;

        int a = root->val;
        int rem = a % 2;
        if( l % 2 == 0 ) {
            // even indexed level, nodes have odd integer values
            // in strictly increasing order (from left to right).
            if( rem == 0 || m[l] >= a ) {
                r = false;
                return;
            }
            m[l] = a;

        } else {
            // odd-indexed level, nodes have even integer values
            // in strictly decreasing order (from left to right)
            if( rem != 0 || m[l] <= a ) {
                r = false;
                return;
            }
            m[l] = a;
        }

        _walk(root->left, l + 1);
        _walk(root->right, l + 1);
    }

public:
    bool isEvenOddTree(TreeNode* root) {
        if( root->left == nullptr && root->right == nullptr )
            return root->val % 2 == 0 ? false : true;

        for(int i = 0; i < 100000; ++i) {
            m[i] = i % 2 == 0 ? -1 : 1000001;
        }

        r = true;
        _walk(root,0);
        return r;
    }
};
