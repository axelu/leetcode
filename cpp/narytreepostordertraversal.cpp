
// 590. N-ary Tree Postorder Traversal
// https://leetcode.com/problems/n-ary-tree-postorder-traversal/




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
// inspired by https://www.geeksforgeeks.org/iterative-postorder-traversal/
class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> ans;
        if( root == nullptr ) return ans;

        // iterative
        stack<Node*> stck1,stck2;
        stck1.push(root);
        Node* curr;
        while(!stck1.empty()) {
            curr = stck1.top();
            stck1.pop();
            stck2.push(curr);
            for(int i = 0; i < curr->children.size(); ++i)
                stck1.push(curr->children[i]);
        }

        while(!stck2.empty()) {
            ans.push_back(stck2.top()->val);
            stck2.pop();
        }

        return ans;
    }
};
