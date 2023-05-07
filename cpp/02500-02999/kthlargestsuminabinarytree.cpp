
// 2583. Kth Largest Sum in a Binary Tree
// https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree/



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
    long long kthLargestLevelSum(TreeNode* root, int k) {

        vector<long long> level_sums;

        // BFS
        queue<TreeNode*> q;
        q.push(root);

        while( !q.empty() ) {

            queue<TreeNode*> q_new;

            long long t = 0;
            while( !q.empty() ) {
                t += (long long)q.front()->val;
                if( q.front()->left != nullptr )
                    q_new.push(q.front()->left);
                if( q.front()->right != nullptr )
                    q_new.push(q.front()->right);
                q.pop();
            }
            level_sums.push_back(t);
            q = q_new;
        }

        if( level_sums.size() < k )
            return -1;

        sort(level_sums.begin(),level_sums.end(),greater<long long>());

        return level_sums[k-1];
    }
};
