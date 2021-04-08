
// 637. Average of Levels in Binary Tree
// https://leetcode.com/problems/average-of-levels-in-binary-tree/



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
    double avge(vector<int> v) {
        double n = v.size();
        double sum = 0.0;
        for(int i : v) sum +=i;
        return sum/n;
    }
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> ans;
        if( root == nullptr ) return ans;

        // BFS
        queue<pair<TreeNode*,int>> q;
        pair<TreeNode*,int> qe;
        q.push({root,0});
        int currLevel = 0;
        vector<int> v;
        while(!q.empty()) {
            qe = q.front();
            q.pop();
            if( qe.second != currLevel ) {
                ans.push_back(avge(v));
                v.clear();
                currLevel = qe.second;
            }
            v.push_back(qe.first->val);
            if( qe.first->left != nullptr )
                q.push({qe.first->left,qe.second+1});
            if( qe.first->right != nullptr )
                q.push({qe.first->right,qe.second+1});
        }
        // finish up
        if( !v.empty() ) ans.push_back(avge(v));
        return ans;
    }
};
