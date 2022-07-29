
// 2049. Count Nodes With the Highest Score
// https://leetcode.com/problems/count-nodes-with-the-highest-score/



class Solution {
private:
    struct TreeNode {
        int val;
        long cnt; // number of nodes in subtrees including this node
        TreeNode * left;
        TreeNode * right;
        TreeNode(int x) : val(x), cnt(1), left(nullptr), right(nullptr) {}
    };

    int dfs(TreeNode * tn) {
        if( tn == nullptr )
            return 0;

        tn->cnt += dfs(tn->left);
        tn->cnt += dfs(tn->right);

        return tn->cnt;
    }

public:
    int countHighestScoreNodes(vector<int>& parents) {
        long n = parents.size();
        vector<TreeNode*> p(n,nullptr);
        p[0] = new TreeNode(0); // root
        for(int i = 1; i < n; ++i) {
            // parent
            if( p[parents[i]] == nullptr )
                p[parents[i]] = new TreeNode(parents[i]);
            TreeNode * par = p[parents[i]];

            // child
            if( p[i] == nullptr )
                p[i] = new TreeNode(i);
            TreeNode * tn = p[i];

            // attach child to parent
            if( par->left == nullptr )
                par->left = tn;
            else
                par->right = tn;
        }

        dfs(p[0]);

        map<long,int> mp; // product,count
        for(int i = 0; i < n; ++i) {
            TreeNode * tn = p[i];
            // we are removing the current node
            // left child count
            long lc = 0;
            long lf = 1;
            if( tn->left != nullptr )
                lc = lf = tn->left->cnt;
            // right child count
            long rc = 0;
            long rf = 1;
            if( tn->right != nullptr )
                rc = rf = tn->right->cnt;
            // that leaves the rest with the parent (if any in case of root)
            long pf = 1;
            long pc = n - lc - rc - 1;
            if( pc )
                pf = pc;

            ++mp[lf*rf*pf];
        }

        return prev(mp.end())->second;
    }
};
