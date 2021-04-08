
// 559. Maximum Depth of N-ary Tree
// https://leetcode.com/problems/maximum-depth-of-n-ary-tree/

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
    int mxk; // max depth

    void dfs(Node* root, int k) {
        if( root == nullptr ) return;
        mxk = max(mxk,k+1);
        for(auto it = begin(root->children); it != end(root->children); ++it)
            dfs(*it,k+1);
    }
public:
    int maxDepth(Node* root) {
        if( root == nullptr ) return 0;

        mxk = 1;
        for(auto it = begin(root->children); it != end(root->children); ++it)
            dfs(*it,1);

        return mxk;
    }
};
