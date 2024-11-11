
// 3331. Find Subtree Sizes After Changes
// https://leetcode.com/problems/find-subtree-sizes-after-changes/





class Solution {
private:
    struct TreeNode {
        int val;
        char c;
        vector<TreeNode*> children;
        TreeNode(int val, char c) : val(val), c(c), children({}) {}
    };


    void dfs(TreeNode* root, vector<int> last[], vector<int>& parent) {

        // determine my 'new' parent
        // (maybe my current parent)
        int c = root->c - 'a';
        if( !last[c].empty() ) {
            parent[root->val] = last[c].back();
        }

        last[c].push_back(root->val);

        for(auto it = root->children.begin(); it != root->children.end(); ++it) {
            dfs(*it, last, parent);
        }

        // backtrack
        last[c].pop_back();
    }


    int dfs(TreeNode* root, vector<int>& ans) {

        int ret = 1; // me

        for(auto it = root->children.begin(); it != root->children.end(); ++it) {
            ret += dfs(*it, ans);
        }

        ans[root->val] = ret;
        return ret;
    }

public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size(); // parent.size() == s.size()

        vector<int> ans(n, -1);

        // Tree is rooted in node 0
        // hence parent[0] == -1
        TreeNode* root = new TreeNode(0, s[0]);

        vector<TreeNode*> treeNodes(n, nullptr);
        treeNodes[0] = root;

        for(int i = 1; i < n; ++i) {
            if( treeNodes[i] == nullptr ) {
                treeNodes[i] = new TreeNode(i, s[i]);
            }
            TreeNode* child = treeNodes[i];

            if( treeNodes[parent[i]] == nullptr ) {
                treeNodes[parent[i]] = new TreeNode(parent[i], s[parent[i]]);
            }
            TreeNode* prnt = treeNodes[parent[i]];

            prnt->children.push_back(child);
        }

        vector<int> last[26]; // last[i].back() contains last node where we saw char i
        dfs(root,last,parent);

        // parent now contains our updated tree
        /*
        for(int i = 0; i < n; ++i)
            cout << i << ":" << parent[i] << " ";
        cout << endl;
        */

        root = new TreeNode(0, s[0]);

        treeNodes.assign(n, nullptr);
        treeNodes[0] = root;

        for(int i = 1; i < n; ++i) {
            if( treeNodes[i] == nullptr ) {
                treeNodes[i] = new TreeNode(i, s[i]);
            }
            TreeNode* child = treeNodes[i];

            if( treeNodes[parent[i]] == nullptr ) {
                treeNodes[parent[i]] = new TreeNode(parent[i], s[parent[i]]);
            }
            TreeNode* prnt = treeNodes[parent[i]];

            prnt->children.push_back(child);
        }

        dfs(root,ans);

        return ans;
    }
};
