
// 1522. Diameter of N-Ary Tree
// https://leetcode.com/problems/diameter-of-n-ary-tree/



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
private:
    int ans;

    int dfs(Node* root, int depth) {
        int n = root->children.size();
        if( n == 0 ) return depth;

        priority_queue<int> pq;
        int t;
        for(int i = 0; i < n; ++i) {
            t = dfs(root->children[i],depth+1);
            pq.push(t);
        }

        // max depth reachable from this node
        int mx1 = pq.top();
        pq.pop();
        if( mx1-depth > ans )
            ans = mx1-depth;
        // second largest depth reachable from this node
        if( !pq.empty() ) {
            int mx2 = pq.top();
            // longest path via the current node
            if( (mx1-depth)+(mx2-depth) > ans )
                ans = (mx1-depth)+(mx2-depth);
        }
        return mx1;
    }
public:
    int diameter(Node* root) {
        if( root == nullptr ) return 0;
        ans = 0;
        dfs(root,0);
        return ans;
    }
};
