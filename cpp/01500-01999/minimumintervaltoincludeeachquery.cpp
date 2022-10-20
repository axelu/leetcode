
// 1851. Minimum Interval to Include Each Query
// https://leetcode.com/problems/minimum-interval-to-include-each-query/



class Solution {
private:
    int * t;
    bool * marked;

    void push(int v) {
        if (marked[v]) {
            t[v*2] = min(t[v],t[v*2]);
            t[v*2+1] = min(t[v],t[v*2+1]);
            marked[v*2] = marked[v*2+1] = true;
            marked[v] = false;
        }
    }

    void update(int v, int tl, int tr, int l, int r, int new_val) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            t[v] = min(t[v],new_val);
            marked[v] = true;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), new_val);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, new_val);
        }
    }

    int get(int v, int tl, int tr, int pos) {
        if (tl == tr) {
            return t[v];
        }
        //if( marked[v] )
        //    return t[v];
        push(v);
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            return get(v*2, tl, tm, pos);
        else
            return get(v*2+1, tm+1, tr, pos);
    }

public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        int mx = 0;
        for(auto& v: intervals)
            mx = max(mx,v[1]);

        t = new int[mx*4];
        marked = new bool[mx*4];
        for(int i = 0; i < mx*4; ++i) {
            t[i] = 10000001;
            marked[i] = 0;
        }

        for(auto& v: intervals)
            update(1,0,mx,v[0],v[1],v[1]-v[0]+1);

        int k = queries.size();
        vector<int> ans(k);
        for(int i = 0; i < k; ++i) {
            int t = get(1,0,mx,queries[i]);
            ans[i] = t != 10000001 ? t : -1;
        }

        return ans;
    }
};
