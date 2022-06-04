
// 1439. Find the Kth Smallest Sum of a Matrix With Sorted Rows
// https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/



class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        int m = mat.size();    // rows
        if( m == 1 )
            return mat[0][k-1];

        int n = mat[0].size(); // cols

        int s = 0;
        for(int i = 0; i < m; ++i)
            s += mat[i][0];

        if( n == 1 || k == 1 )
            return s;

        auto cmp = [m](const vector<int>& a, const vector<int>& b) {
            if( a[m] > b[m] )
                return true;
            return false;
        };
        priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)> pq(cmp);

        vector<int> v(m+1,0); // last element will hold sum
        v[m] = s; // s is the 1st smallest array sum
        pq.push(v);

        // we need to avoid duplicates
        set<vector<int>> seen;
        seen.insert(v);

        while(true) {
            v = pq.top();
            pq.pop();

            if( --k == 0 )
                break;

            for(int i = 0; i < m; ++i) {
                if( v[i] < n-1 ) {
                    v[m] -= mat[i][v[i]];
                    v[m] += mat[i][v[i]+1];
                    ++v[i];
                    auto p = seen.insert(v);
                    if( p.second )
                        pq.push(v);
                    // back track
                    --v[i];
                    v[m] -= mat[i][v[i]+1];
                    v[m] += mat[i][v[i]];
                }
            }
        }

        return v[m];
    }
};
