
// 429. N-ary Tree Level Order Traversal
// https://leetcode.com/problems/n-ary-tree-level-order-traversal/




/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> ans;
        if( root == nullptr ) return ans;

        // BFS
        queue<pair<Node*,int>> q;
        pair<Node*,int> qe;
        q.push({root,0});
        int currLevel = 0;
        vector<int> v;
        while(!q.empty()) {
            qe = q.front();
            q.pop();
            if( qe.second != currLevel ) {
                ans.push_back(v);
                v.clear();
                currLevel = qe.second;
            }
            v.push_back(qe.first->val);
            for(int i = 0; i < qe.first->children.size(); ++i)
                q.push({qe.first->children[i],qe.second+1});
        }
        // finish up
        if( !v.empty() ) ans.push_back(v);
        return ans;
    }
};
