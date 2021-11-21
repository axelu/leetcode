
// 117. Populating Next Right Pointers in Each Node II
// https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
// day 6 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/569/week-1-december-1st-december-7th/3556/



/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
private:
    queue<pair<Node*,int>> q;

public:
    Node* connect(Node* root) {
        if( root == nullptr ) return root;

        q.push({root,0});
        pair<Node*,int> currQe;
        pair<Node*,int> priorQe{nullptr,-1};
        while( !q.empty() ) {
            currQe = q.front();
            q.pop();
            // cout << currQe.first->val << " " << currQe.second << endl;
            if( priorQe.second == currQe.second ) priorQe.first->next = currQe.first;
            if( currQe.first->left != nullptr ) q.push({currQe.first->left,currQe.second+1});
            if( currQe.first->right != nullptr ) q.push({currQe.first->right,currQe.second+1});
            priorQe = currQe;
        }
        return root;

    }
};
