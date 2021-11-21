
// 1506. Find Root of N-Ary Tree
// https://leetcode.com/problems/find-root-of-n-ary-tree/
// day 8 Janyary 2021 challenge bonus question
// https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/580/week-2-january-8th-january-14th/3596/




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
    Node* findRoot(vector<Node*> tree) {
        size_t n = tree.size();
        if( n == 1 ) return tree[0];

        // node with no child[ren] is a leaf and with that not the root
        // a child node is exactly that, a child and with that not the root
        // node that is not a child of any other node is the root
        unordered_map<int,Node*> rootCandidates;    // each node has a unique value
        unordered_set<int> childNodeValues;         // each node has a unique value
        size_t nbrChildren;
        Node* curNode;
        Node* curChild;
        for(int i = 0; i < n; ++i) {
            curNode = tree[i];
            nbrChildren = curNode->children.size();
            if( nbrChildren == 0 ) {
                // leaf node is a child node
                childNodeValues.insert(curNode->val);
                continue;
            }
            // if I am a child, I cannot be the root, otherwise I could be the root
            if( childNodeValues.find(curNode->val) == childNodeValues.end() )
                rootCandidates.insert({curNode->val,curNode});
            for(int j = 0; j < nbrChildren; ++j) {
                curChild = curNode->children[j];
                childNodeValues.insert(curChild->val);
                // child nodes cannot be root nodes
                rootCandidates.erase(curChild->val);
            }
        }

        // if root candidates only contains 1 node, that is the root
        // otherwise we check the candidates till we find one that is not a child
        if( rootCandidates.size() == 1 ) return rootCandidates.begin()->second;
        unordered_set<int>::iterator ite = childNodeValues.end();
        for(auto it = rootCandidates.begin(); it != rootCandidates.end(); ++it)
            if( childNodeValues.find(it->first) == ite )
                return it->second;

        return nullptr;
    }
};
