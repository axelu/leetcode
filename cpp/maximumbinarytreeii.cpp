
// Maximum Binary Tree II
// https://leetcode.com/problems/maximum-binary-tree-ii/



#include <iostream>
#include <cassert>

#include <vector>
#include <algorithm>

using namespace std;


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
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        if( root == nullptr ) return new TreeNode(val);
        if( root->val < val ) {
            TreeNode* tn = new TreeNode(val);
            tn->left = root;
            return tn;
        }

        vector<int> nums = _deconstruct(root);
        for(int i : nums) cout << i << " ";
        cout << endl;

        nums.push_back(val);
/*
        // find last element greater than val
        auto it1 = find_if(nums.rbegin(), nums.rend(),[val](int i) {
            return i > val;
        });
        // find max element between last element greater than val and end
        auto it2 = max_element(it1.base(), nums.end());

        int offset = ( it2 == nums.end() ) ? 0 : 1;
        nums.insert(it2 + offset, val);
*/
        for(int i : nums) cout << i << " ";
        cout << endl;

        return _build(nums.begin(), nums.end());
    }

    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return _build(nums.begin(), nums.end());
    }
private:
    vector<int> _deconstruct(TreeNode* root) {
        if( root == nullptr ) return {};

        vector<int> l = _deconstruct(root->left);
        vector<int> r = _deconstruct(root->right);

        l.push_back(root->val);
        l.insert(l.end(),r.begin(),r.end());
        return l;
    }

    TreeNode* _build(vector<int>::iterator itb, vector<int>::iterator ite) {
        if( ite - itb == 0 ) return nullptr;

        auto me = max_element(itb, ite);
        TreeNode* r = new TreeNode(*me);

        r->left = _build(itb, me);
        r->right = _build(me + 1, ite);

        return r;
    }
};

int main() {
    Solution s;
/*
    vector<int> v1 = {1,4,2,3};
    TreeNode* t1 = s.constructMaximumBinaryTree(v1);
    TreeNode* r1 = s.insertIntoMaxTree(t1, 5);
*/
    vector<int> v2 = {2,1,5,4};
    TreeNode* t2 = s.constructMaximumBinaryTree(v2);
    TreeNode* r2 = s.insertIntoMaxTree(t2, 3);

    vector<int> v3 = {6,10,8};
    TreeNode* t3 = s.constructMaximumBinaryTree(v3);
    TreeNode* r3 = s.insertIntoMaxTree(t3, 9);

    // case 68
    vector<int> v4 = {1,7,2,6,8,4,3};
    TreeNode* t4 = s.constructMaximumBinaryTree(v4);
    TreeNode* r4 = s.insertIntoMaxTree(t4, 5);

  return 0;
}
