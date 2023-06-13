
// 2438. Range Product Queries of Powers
// https://leetcode.com/problems/range-product-queries-of-powers/






class Solution {
private:
    long mod = 1000000007;
    long t[4*31]; // segment tree holding modular product

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = (t[v*2] * t[v*2+1]) % mod;
        }
    }

    long product(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 1;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return (product(v*2, tl, tm, l, min(r, tm))
               * product(v*2+1, tm+1, tr, max(l, tm+1), r)) % mod;
    }

public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {

        vector<int> p2;
        long p = 1;
        for(int i = 0; i < 31; ++i) {
            if( (n >> i) & 1 )
                p2.push_back(p);
            p *= 2;
        }
        // debug
        //for(int i = 0; i < p2.size(); ++i)
        //    cout << p2[i] << " ";
        //cout << endl;

        // build segment tree
        build(p2,1,0,p2.size()-1);

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i)
            ans[i] = product(1,0,p2.size()-1,queries[i][0],queries[i][1]);

        return ans;
    }
};
