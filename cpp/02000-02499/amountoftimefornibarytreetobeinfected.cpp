
// 2385. Amount of Time for Binary Tree to Be Infected
// https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/




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
    // depth first search
    void dfs(TreeNode* tn, unordered_map<int,vector<int>>& g) {

        // left
        if( tn->left != nullptr ) {
            g[tn->val].push_back(tn->left->val);
            g[tn->left->val].push_back(tn->val);
            dfs(tn->left,g);
        }
        // right
        if( tn->right != nullptr ) {
            g[tn->val].push_back(tn->right->val);
            g[tn->right->val].push_back(tn->val);
            dfs(tn->right,g);
        }

        return;
    }

public:
    int amountOfTime(TreeNode* root, int start) {

        unordered_map<int,vector<int>> g; // undirected graph
        dfs(root,g);

        // BFS breadth first search
        unordered_set<int> seen;
        queue<array<int,2>> q;
        q.push({start,0});
        seen.insert(start);

        int ans = 0;

        while( !q.empty() ) {
            int u = q.front()[0];
            int dist = q.front()[1];
            q.pop();
            ans = max(ans,dist);

            for(int v: g[u])
                if( seen.insert(v).second )
                    q.push({v,dist+1});
        }

        return ans;
    }
};
