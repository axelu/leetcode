
// 1310. XOR Queries of a Subarray
// https://leetcode.com/problems/xor-queries-of-a-subarray/




class Solution {
private:
    private:
    int t[120000]; // segment tree

    void build(int a[], int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = t[v*2] ^ t[v*2+1];
        }
    }

    int XOR(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return XOR(v*2, tl, tm, l, min(r, tm))
               ^ XOR(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        size_t n = arr.size();
        size_t m = queries.size();
        vector<int> ans;
        if( n == 0 || m == 0 ) return ans;
        build(arr.data(),1,0,n-1);
        for(int i = 0; i < m; ++i)
            ans.push_back(XOR(1,0,n-1,queries[i][0],queries[i][1]));
        return ans;
    }
};
