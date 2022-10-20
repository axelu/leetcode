
// 2378. Choose Edges to Maximize Score in a Tree
// https://leetcode.com/problems/choose-edges-to-maximize-score-in-a-tree/



class Solution {
private:
    struct TreeNode{
        int id;
        vector<pair<TreeNode*,int>> children;
        TreeNode(int x) : id(x), children({}) {}
    };

    pair<long long,long long> dfs(TreeNode * tn) {
        // cout << "dfs " << tn->id << endl;
        // returns a pair of long long
        // pair.first is the max when our current node's incoming edge was selected
        // pair.second is the max when our current node's incoming edge was NOT selected

        int n = tn->children.size();
        // cout << n << endl;
        // leaf node
        if( n == 0 )
            return {0,0};

        // if our current node's incoming edge was selected, then
        // we cannot use any of the edges to our children to contribute to our score
        // our return is sum of childisecond for each of our children

        // if our node's incoming edge was NOT selected, then
        // we are free to choose any edge to a child and its score when its edge was selected,
        // but only one + score of all remaining children with their edge not selected
        // not selecting any edge is an option also, if that has a higher score

        long long sum = 0; // sum of childisecond
        vector<pair<long long,long long>> si(n);

        for(int i = 0; i < n; ++i) {
            auto p = dfs(tn->children[i].first);
            sum += p.second;
            si[i] = p;
        }

        long long a = LLONG_MIN;

        for(int i = 0; i < n; ++i) {
            long long b = tn->children[i].second + si[i].first + (sum - si[i].second);
            a = max(a,b);
        }

        return {sum,max(a,sum)};
    }

public:
    long long maxScore(vector<vector<int>>& edges) {
        int n = edges.size();
        if( n == 1 )
            return 0;

        vector<TreeNode*> tns(n,nullptr);

        TreeNode * root = new TreeNode(0);
        tns[0] = root;
        for(int i = 1; i < n; ++i) {
            int paridx = edges[i][0];
            int weight = edges[i][1];

            if( tns[i] == nullptr )
                tns[i] = new TreeNode(i);

            // attach child to parent
            if( tns[paridx] == nullptr )
                tns[paridx] = new TreeNode(paridx);
            tns[paridx]->children.push_back({tns[i],weight});
        }

        auto p = dfs(root);
        // cout << p.first << " " << p.second << endl;
        return max(p.first,p.second);
    }
};
