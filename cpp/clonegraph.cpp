
// Clone Graph
// day 20 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/561/week-3-october-15th-october-21st/3501/
// https://leetcode.com/problems/clone-graph/




/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }

    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
private:
    void clone(Node* toClone, Node* from, Node* nodes[]) {
        int val = toClone->val;
        for(Node* neighbor : from->neighbors)
            if( val == neighbor->val ) return;

        Node* node;
        if( nullptr == nodes[val] ) {
            node = new Node(val);
            nodes[val] = node;
        } else {
            node = nodes[val];
        }

        // create bidirectional edge
        from->neighbors.push_back(node);
        node->neighbors.push_back(from);

        for(Node* neighbor : toClone->neighbors)
            clone(neighbor,node,nodes);
    }
public:
    Node* cloneGraph(Node* node) {
        if( node == nullptr ) return nullptr;

        Node* r = new Node(node->val);
        if( node->neighbors.empty() ) return r;

        Node* nodes[101] = {};
        nodes[1] = r;
        for(Node* neighbor : node->neighbors) {
            clone(neighbor,r,nodes);
        }

        return r;
    }
};
