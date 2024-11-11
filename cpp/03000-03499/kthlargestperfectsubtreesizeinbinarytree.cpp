
// 3319. K-th Largest Perfect Subtree Size in Binary Tree
// https://leetcode.com/problems/k-th-largest-perfect-subtree-size-in-binary-tree/







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
    priority_queue<int> pq; // depth of perfect subtree
    // TODO we could limit our pq to k entries on every push using a multiset

    int dfs(TreeNode* root) {
        if( root == nullptr )
            return -1;

        if( root->left == nullptr && root->right == nullptr ) {
            // we are at a leave, a perfect binary subtree of size 1
            pq.push(1);
            return 1;
        }

        int a = dfs(root->left);
        int b = dfs(root->right);

        if( a != -1 && a == b ) {
            // we are at a parent that is the root of a perfect subtree
            pq.push(1 + a);
            return 1 + a;
        } else {
            return -1;
        }
    }

public:
    int kthLargestPerfectSubtree(TreeNode* root, int k) {
        dfs(root);
        if( pq.size() < k )
            return -1;

        int i = 0;
        while( true ) {
            ++i;
            if( i == k )
                return pow(2,pq.top()) - 1;
            pq.pop();
        }

        return -1; // we should never get here
    }
};
