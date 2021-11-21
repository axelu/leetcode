
// 1490. Clone N-ary Tree
// https://leetcode.com/problems/clone-n-ary-tree/



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
    void clone1(Node* root, unordered_map<Node*,Node*>& um) {
        um.insert({root,new Node(root->val)});
        for(int i = 0; i < root->children.size(); ++i)
            clone1(root->children[i],um);
    }

    void clone2(Node* root, unordered_map<Node*,Node*>& um) {
        Node* clone = um.find(root)->second;
        for(int i = 0; i < root->children.size(); ++i) {
            clone->children.push_back(um.find(root->children[i])->second);
            clone2(root->children[i],um);
        }
    }

public:
    Node* cloneTree(Node* root) {
        if( root == nullptr ) return nullptr;
        unordered_map<Node*,Node*> um;
        clone1(root,um);
        clone2(root,um);
        return um.find(root)->second;
    }
};
