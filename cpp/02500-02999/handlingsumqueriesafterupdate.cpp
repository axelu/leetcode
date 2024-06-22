
// 2569. Handling Sum Queries After Update
// https://leetcode.com/problems/handling-sum-queries-after-update/





class Solution {
private:
    struct T {
        int total;
        int totalon;
        T() : total(0), totalon(0) {}
    };

    T * t; // segment tree, lazy propagation
    bool * marked;

    void build(vector<int>& nums1, int v, int tl, int tr) {
        if (tl == tr) {
            t[v].total = 1;
            t[v].totalon = nums1[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(nums1, v*2, tl, tm);
            build(nums1, v*2+1, tm+1, tr);
            // combine
            t[v].total = t[v*2].total + t[v*2+1].total;
            t[v].totalon = t[v*2].totalon + t[v*2+1].totalon;
        }
    }

    void push(int v) {
        if (marked[v]) {
            t[v*2].totalon = t[v*2].total - t[v*2].totalon;       // flip
            // marked[v*2] = true;
            marked[v*2] = !marked[v*2];
            t[v*2+1].totalon = t[v*2+1].total - t[v*2+1].totalon; // flip
            // marked[v*2+1] = true;
            marked[v*2+1] = !marked[v*2+1];

            marked[v] = false;
        }
        return;
    }

    // range update
    void update(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            t[v].totalon = t[v].total - t[v].totalon; // flip
            marked[v] = !marked[v];
            // marked[v] = true;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm));
            update(v*2+1, tm+1, tr, max(l, tm+1), r);
            t[v].totalon = t[v*2].totalon + t[v*2+1].totalon;
        }
    }

public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        int n = nums1.size(); // nums1.length = nums2.length

        long long sum = accumulate(nums2.begin(),nums2.end(),0LL);

        T _t[4*n]; t = _t;
        bool _marked[4*n];memset(_marked,false,sizeof _marked); marked = _marked;

        build(nums1, 1, 0, n-1);
        // cout << "t[1].total " << t[1].total << " t[1].totalon " << t[1].totalon << endl;

        vector<long long> ans;

        int q_sz = queries.size(); // TODO we only need to process up to last query type 3
        for(int i = 0; i < q_sz; ++i) {
            int query_type = queries[i][0]; // 1, 2 or 3
            if( query_type == 1 ) {
                int l = queries[i][1];
                int r = queries[i][2];
                update(1, 0, n-1, l, r);
                // cout << "i " << i << " type 1 l " << l << " r " << r << " t[1].total " << t[1].total << " t[1].totalon " << t[1].totalon << endl;

            } else if( query_type == 2 ) {
                // cout << "i " << i << " type 2 l " << " t[1].totalon " << t[1].totalon << endl;
                long long p = queries[i][1];
                sum += (long long)t[1].totalon * p;

            } else { // query_type == 3
                ans.push_back(sum);

            }
        }

        return ans;
    }
};
