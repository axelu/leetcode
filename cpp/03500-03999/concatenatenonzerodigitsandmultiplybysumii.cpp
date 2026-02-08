
// 3756. Concatenate Non-Zero Digits and Multiply by Sum II
// https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-ii/





// initialize once
long pow10[100001];
bool init = false;

class Solution {
private:
    const long mod = 1000000007;

    // array 0: x % mod, 1: sum of digits in x, 2: num of non-zero digits
    array<long,3> t[400000]; // segment tree, range query

    array<long,3> combine(array<long,3>& lhs, array<long,3>& rhs) {
        if( lhs[2] == 0 )
            return rhs;
        if( rhs[2] == 0 )
            return lhs;

        array<long,3> ret;
        ret[0] = (lhs[0] * pow10[rhs[2]]) % mod;
        ret[0] = (ret[0] + rhs[0]) % mod;
        ret[1] = lhs[1] + rhs[1]; // always < mod
        ret[2] = lhs[2] + rhs[2]; // always < mod
        return ret;
    }

    void build(string& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v][0] = a[tl]-'0';
            t[v][1] = a[tl]-'0';
            t[v][2] = a[tl] != '0' ? 1 : 0;
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    // range query
    array<long,3> rq(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return {0,0,0};
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        auto lhs = rq(v*2, tl, tm, l, min(r, tm));
        auto rhs = rq(v*2+1, tm+1, tr, max(l, tm+1), r);
        return combine(lhs, rhs);
    }


public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        if( !init ) {
            pow10[0] = 1;
            for(int i = 1; i <= 100000; ++i)
                pow10[i] = (pow10[i-1] * 10L) % mod;
            init = true;
        }

        int n = s.size(); // 1 <= n <= 1e5

        build(s, 1, 0, n-1);

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            auto res = rq(1, 0, n-1, queries[i][0], queries[i][1]);
            ans[i] = (res[0] * res[1]) % mod;
        }

        return ans;
    }
};
