
// 2736. Maximum Sum Queries
// https://leetcode.com/problems/maximum-sum-queries/





class Solution {
private:
    int t[400000]; // segment tree memory efficient indexing

    int get_max(int v, int tl, int tr, int l, int r) {
        // cout << "get_max v " << v << " tl " << tl << " tr " << tr << " l " << l << " r " << r << endl;
        if (l > r)
            return -1;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return max(get_max(v+1, tl, tm, l, min(r, tm)),
                   get_max(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r));
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            t[v] = max(t[v],new_val);
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v+1, tl, tm, pos, new_val);
            else
                update(v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

public:
    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        int n = nums1.size(); // n == nums1.size() == nums2.size(); 1 <= n <= 1e5

        // sort nums1 in conjunction with nums2
        // get unique values in nums2
        priority_queue<vector<int>> pq;
        set<int> us; // collect unique values in nums2 and queries y
        for(int i = 0; i < n; ++i) {
            pq.push({nums1[i],nums2[i]});
            us.insert(nums2[i]);
        }

        // sort queries
        int q_sz = queries.size();
        vector<vector<int>> _queries(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            _queries[i] = {queries[i][0],queries[i][1],i};
            us.insert(queries[i][1]);
        }
        sort(_queries.begin(),_queries.end(),[](const vector<int>& a, const vector<int>& b){
            if( a[0] > b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] > b[1] ) {
                    return true;
                }
            }
            return false;
        });

        int k = 0;
        unordered_map<int,int> um;
        for(int val: us)
            um[val] = k++;

        // init segment tree
        memset(t,-1,sizeof t);
        int tr = k - 1;

        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            int x = _queries[i][0];
            int y = _queries[i][1];
            int q = _queries[i][2];

            while( !pq.empty() && pq.top()[0] >= x ) {
                int val_nums1 = pq.top()[0];
                int val_nums2 = pq.top()[1];
                int pos = um[val_nums2];
                pq.pop();
                update(1, 0, tr, pos, val_nums1 + val_nums2);
            }

            ans[q] = get_max(1, 0, tr, um[y], tr);
        }

        return ans;
    }
};
