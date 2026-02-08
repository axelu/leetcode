
// 3748. Count Stable Subarrays
// https://leetcode.com/problems/count-stable-subarrays/



class Solution {
private:

    // brute force
    long long bf(vector<int>& nums, int n, int l, int r) {
        // l <= r
        if( l == r )
            return 1L;

        long long ret = 0LL;

        // get number of non-decreasing runs
        // between l and r inclusive
        int s = l;
        long long len, t;
        int i = l+1;
        for(; i <= r; ++i) {
            if( nums[i] < nums[i-1] ) {
                len = i - s;
                t = len * (len+1LL)/2LL;
                ret += t;
                s = i;
            }
        }
        // finish up
        len = i - s;
        t = len * (len+1LL)/2LL;
        ret += t;

        return ret;
    }

public:
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        if( n == 1 )
            return {1LL};

        // we will record and index non-dereasing intervals
        vector<int> iindices(n); // nums idx to interval index
        iindices[0] = 0;
        vector<vector<int>> intervals; // {{begin,end},...}
        intervals.push_back({0,-1});
        int iidx = 0;
        for(int i = 1; i < n; ++i) {
            if( nums[i] < nums[i-1] ) {
                // a non-decreasing interval
                // end   i-1
                intervals[iidx][1] = i-1;
                ++iidx;

                // a new interval
                // begin i
                intervals.push_back({i,-1});
            }
            iindices[i] = iidx;
        }
        // finish up
        intervals[iidx][1] = n-1;

        int intervals_sz = intervals.size(); // == iidx + 1

        // we need to be able to do range sum queries
        // as we have no modifications, use prefixSum
        vector<long long> prefixSum(intervals_sz+1);
        for(int i = 1; i <= intervals_sz; ++i) {
            int l = intervals[i-1][0];
            int r = intervals[i-1][1];
            long long len = r - l + 1;
            long long val = len * (len+1LL)/2LL;
            prefixSum[i] = prefixSum[i-1] + val;
        }

        int q = queries.size();

        vector<long long> ans(q);

        for(int i = 0; i < q; ++i) {
            int l = queries[i][0];
            int r = queries[i][1];

            // brute force, no preprocessing needed
            // ans[i] = bf(nums, n, l, r);

            int liidx = iindices[l];
            int riidx = iindices[r];

            if( liidx == riidx ) {
                // l and r are part of the same non-decreasing interval
                long long len = r - l + 1;
                ans[i] = len * (len+1LL)/2LL;
                continue;
            }

            //    l                r
            // ----- --- ... --- -----

            long long t = 0LL;

            int ql = liidx;
            int lbegin = intervals[liidx][0];
            int lend   = intervals[liidx][1];
            if( lbegin < l ) {
                // l lies on a non-decreasing interval
                long long len = lend - l + 1;
                t += len * (len+1LL)/2LL;
                ql += 1;
            }

            int qr = riidx;
            int rbegin = intervals[riidx][0];
            int rend   = intervals[riidx][1];
            if( rend > r ) {
                // r lies on a non-decreasing interval
                long long len = r - rbegin + 1;
                t += len * (len+1LL)/2LL;
                qr -= 1;
            }

            t += prefixSum[qr+1] - prefixSum[ql];

            ans[i] = t;
        }

        return ans;
    }
};
