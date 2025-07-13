
// 3575. Maximum Good Subtree Score
// https://leetcode.com/problems/maximum-good-subtree-score/





class Solution {
private:
    pair<bool,int> good_int(int n) {
        // return {good or bad, mask if good}

        int mask = 0;

        // 1 <= n <= 1e9
        while( n ) {
            int rem = n % 10;
            if( mask & (1<<rem) )
                return {false,0};
            mask |= (1<<rem);
            n /= 10;
        }
        return {true,mask};
    }

    const long mod = 1000000007;

    vector<int> * _vals;

    vector<vector<int>> t;
    vector<int> masks;
    vector<int> good;


    long mem[1024][500];
    // nums = nodeids
    long rec(vector<int>& nums, int mask, int pos) {
        int n = nums.size();
        if( pos == n )
            return 0L;

        if( mem[mask][pos] != -1 )
            return mem[mask][pos];

        // we have a choice
        //     skip aka don't take OR
        //     take if we can

        long a = rec(nums, mask, pos+1);

        long b = 0L;
        int u = nums[pos];
        if( good[u] && (mask & masks[u]) == 0 ) {
            int mask_new = (mask | masks[u]);
            b = (long)_vals->at(u) + rec(nums, mask_new, pos+1);
        }

        return mem[mask][pos] = max(a,b);
    }

    vector<long> maxScore;

    vector<int> dfs(int u) {


        // we are returning the list of all nodeids
        // in our subtree including us, that are good to begin with

        vector<int> ret;
        if( good[u] )
            ret.push_back(u);

        // TODO optimize because it is a tree we could pass this down
        for(int v: t[u] ) {
            auto vec = dfs(v);
            ret.insert(ret.end(), vec.begin(), vec.end());
        }

        // get maxScore[u]
        memset(mem,-1,sizeof mem);
        maxScore[u] = rec(ret, 0, 0);

        return ret;
    }


public:
    int goodSubtreeSum(vector<int>& vals, vector<int>& par) {
        int n = vals.size(); // vals.size() == par.size(); 1 <= n <= 500

        // build tree from parents
        t.resize(n);
        masks.resize(n);
        good.resize(n);
        vector<bool> seen(n,false);
        // node 0
        pair<bool,int> res = good_int(vals[0]);
        good[0] = res.first;
        masks[0] = res.second;
        seen[0] = true;
        for(int c = 1; c < n; ++c) {
            if( !seen[c] ) {
                res = good_int(vals[c]);
                good[c] = res.first;
                masks[c] = res.second;
            }

            int p = par[c];
            if( !seen[p] ) {
                res = good_int(vals[p]);
                good[p] = res.first;
                masks[p] = res.second;
            }

            t[p].push_back(c);
        }

        _vals = &vals;
        maxScore.resize(n,0);

        dfs(0);

        long ans = 0L;
        for(int i = 0; i < n; ++i)
            ans = (ans + maxScore[i]) % mod;

        return ans;
    }
};
