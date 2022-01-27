

// 2096. Step-By-Step Directions From a Binary Tree Node to Another
// https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/


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
    int rec;        // 0 no, 1 yes, 2 stopped
    bool f;         // true if we discovered start before dest
    string steps;   // path


    void dfs(TreeNode* root, int startValue, int destValue, bool recorded, char dir) {
        if( root == nullptr ) {
            if( recorded )
                steps.pop_back();
            return;
        }

        // cout << root->val << endl;

        if( root->val == startValue || root->val == destValue ) {
            // we are at one of the values, either start or destination
            if( rec == 0 ) {
                // we discovered the 1st node
                // turn on recording from this point on forward
                rec = 1;
                if( root->val == destValue ) {
                    // we discovered destination before start
                    // we need to record steps in opposite
                    f = false;
                }
            } else if( rec == 1 ) {
                // because the recording was on,
                // we have discovered the second node
                // stop the recording
                rec = 2;
                return;
            }
        }


        // go left
        bool t = false;
        if( rec == 1 ) {
            t = true;
            if( f )
                steps.push_back('L');
            else
                steps.push_back('U');
        }
        dfs(root->left,startValue,destValue,t,'L');
        if( rec == 2 )
            return;

        // go right
        t = false;
        if( rec == 1 ) {
            t = true;
            if( f )
                steps.push_back('R');
            else
                steps.push_back('U');
        }
        dfs(root->right,startValue,destValue,t,'R');


        if( rec == 1 ) {
            if( recorded ) {
                // backout the step that got us here
                steps.pop_back();
            } else {
                // we need to record us going up
                if( f )
                    steps.push_back('U');
                else
                    steps.push_back(dir);
            }
        }
        return;
    }

public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        // we will do a DFS
        // we may discover the start node before the dest node
        // in that case we reverse the path

        rec = 0;    // initially we don't record
        f = true;   // initially we assume we will discover start before destination
        steps = ""; // initially our path is empty
        char dir = '#';
        dfs(root,startValue,destValue,false,dir);

        // we discovered destination first, hence reverse steps
        if( !f )
            reverse(steps.begin(),steps.end());

        return steps;
    }
};
