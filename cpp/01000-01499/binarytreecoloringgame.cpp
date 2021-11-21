
// 1145. Binary Tree Coloring Game
// https://leetcode.com/problems/binary-tree-coloring-game/



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    struct T {
        TreeNode* node;
        TreeNode* parent;
        int count; // number of nodes in subtree of root plus root itself
        T(TreeNode* node, TreeNode* parent, int count) : node(node), parent(parent), count(count) {}
    };

    T* t[101];

    // DFS
    int buildTree(TreeNode* root, TreeNode* parent) {
        if( root == nullptr ) return 0;

        int cnt = 1;
        cnt += buildTree(root->left,root);
        cnt += buildTree(root->right,root);
        t[root->val] = new T(root,parent,cnt);;
        return cnt;
    }

public:
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        if( n == 1 ) return false;

        buildTree(root,nullptr);
        // three optimal choices: parent if x, left child of x right child of x

        int player1score, player2score;

        // parent of x
        // player 1 confined to subtree of x
        if( t[x]->parent != nullptr ) {
            player1score = t[x]->count;
            player2score = n - player1score;
            if( player2score > player1score ) return true;
        }
        // left child of x
        if( t[x]->node->left != nullptr ) {
            player2score = t[t[x]->node->left->val]->count;
            player1score = n - player2score;
            if( player2score > player1score ) return true;
        }
        // right child of x
        if( t[x]->node->right != nullptr ) {
            player2score = t[t[x]->node->right->val]->count;
            player1score = n - player2score;
            if( player2score > player1score ) return true;
        }
        return false;
    }
};
