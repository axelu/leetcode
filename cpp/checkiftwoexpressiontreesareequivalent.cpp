
// 1612. Check If Two Expression Trees are Equivalent
// https://leetcode.com/problems/check-if-two-expression-trees-are-equivalent/





/**
 * Definition for a binary tree node.
 * struct Node {
 *     char val;
 *     Node *left;
 *     Node *right;
 *     Node() : val(' '), left(nullptr), right(nullptr) {}
 *     Node(char x) : val(x), left(nullptr), right(nullptr) {}
 *     Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    void dfs(Node* root, array<int,26>& cnt) {
        if( root == nullptr ) return;

        if( root->val != '+' ) ++cnt[root->val-'a'];

        dfs(root->left,cnt);
        dfs(root->right,cnt);
    }

public:
    bool checkEquivalence(Node* root1, Node* root2) {
        array<int,26> cnt1{0};
        array<int,26> cnt2{0};

        dfs(root1,cnt1);
        dfs(root2,cnt2);
        return cnt1 == cnt2;
    }
};
