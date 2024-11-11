
// 3161. Block Placement Queries
// https://leetcode.com/problems/block-placement-queries/





class Solution {
private:
    // https://cp-algorithms.com/data_structures/segment_tree.html#assignment-on-segments
    int t[200008];      // segment tree (max), lazy propagation
    int lazy[200008];

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = max(t[v*2], t[v*2 + 1]);
        }
    }

    void push(int v) {
        t[v*2] += lazy[v];
        lazy[v*2] += lazy[v];
        t[v*2+1] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v] = 0;
    }

    // range addition
    void update(int v, int tl, int tr, int l, int r, int addend) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            t[v] += addend;
            lazy[v] += addend;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), addend);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
            t[v] = max(t[v*2], t[v*2+1]);
        }
    }

    // get max
    int query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return INT_MIN;
        if (l == tl && tr == r)
            return t[v];
        push(v);
        int tm = (tl + tr) / 2;
        return max(query(v*2, tl, tm, l, min(r, tm)),
                   query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        // idea: use a segment tree, maximum tree, with adding on segments and range max query
        //     when we place an obstacle at x, then we need to subtract
        //     from segment [x+1, next obstacle] such that t[x+1] = 1, t[x+2] = 2, ...

        // 1 <= x, sz <= min(5 * 1e4, 3 * queries.length)
        vector<int> a(50002);
        iota(a.begin(), a.end(), 0); // 0, 1, 2, ...

        int tr = 50001;
        build(a, 1, 0, tr);

        set<int> obstacles;
        obstacles.insert(tr); // sentinel obstacle on the right end

        vector<bool> ans;
        for(auto& q: queries) {
            if( q[0] == 1 ) {
                int x = q[1];
                // get obstacle to the right
                int r = *obstacles.upper_bound(x); // will always at least find our sentinel
                // determine addend
                int addend = query(1, 0, tr, x, x);
                // update range [obstacle+1, obstacle to the right] to 1, 2, 3, ...
                update(1, 0, tr, x+1, r, -addend);
                // add new obstacle
                obstacles.insert(x); // it is guaranteed that no obstacles at same position

            } else {
                int x = q[1];
                int sz = q[2];

                int mx = query(1, 0, tr, 0, x);
                if( mx >= sz )
                    ans.push_back(true);
                else
                    ans.push_back(false);
            }
        }

        return ans;
    }
};
