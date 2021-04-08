#include <iostream>
#include <cassert>

#include <vector>
#include <map>

using namespace std;

// Binary Tree Level Order Traversal II
// https://leetcode.com/problems/binary-tree-level-order-traversal-ii/


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if ( root == nullptr ) return {};
        if ( root->left == nullptr && root->right == nullptr ) return {{root->val}};

        map<int,vector<int>> m; // holds depth, elements from left to right on that level
        explore(root, 0, m);

        vector<vector<int>> r;
        for(auto it = m.rbegin(); it != m.rend(); ++it) {
            r.push_back(it->second);
        }

        return r;
    }
private:
    void explore(TreeNode* root, int y, map<int,vector<int>>& m) {

        if (root == nullptr) return;

        auto p = m.insert({y,{root->val}});
        if ( !p.second ) {
            p.first->second.push_back(root->val);
        }

        y +=1;
        explore(root->left,y,m);
        explore(root->right,y,m);
    }
};

int main() {

    Solution s;

    TreeNode* root = new TreeNode(3);
    TreeNode* l1 = new TreeNode(9);
    root->left = l1;
    TreeNode* r1 = new TreeNode(20);
    root->right = r1;
    TreeNode* r1l2 = new TreeNode(15);
    r1->left = r1l2;
    TreeNode* r1r2 = new TreeNode(7);
    r1->right = r1r2;
    vector<vector<int>> r = s.levelOrderBottom(root);

    cout << "[";
    for(auto v : r) {
        cout << "[";
        for(auto i : v) {
            cout << i << " ";
        }
        cout << "]";
    }
    cout << "]" << endl;


    return 0;
}
