
// 3634. Minimum Removals to Balance Array
// https://leetcode.com/problems/minimum-removals-to-balance-array/



class Solution {
private:
    // binary search while loop
    int upper_bound(vector<pair<long,int>>& nums, int s, long long target) {
        int n = nums.size();

        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        //     in our case s
        // binary search upper bound while loop
        // upper bound -> greater than target
        // int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= nums[mid].first )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && nums[s].first <= target )
            ++s;

        return s;
    }

    // binary search recursive
    int search(vector<pair<long,int>>& nums, int s, int e, long long k, long long mx) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( nums[mid].first * k >= mx ) {
            // can we do better?
            int t = search(nums, s, mid-1, k, mx);
            return t != -1 ? t : mid;
        }

        return search(nums, mid+1, e, k, mx);
    }

public:
    int minRemoval(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= n<= 1e5
        if( n == 1 )
            return 0;

        // edge case k == 1
        // we could find the element with the most frequency
        // and the answer would be n - mostfrequency

        map<long long, int> mp; // val, count
        for(long long x: nums)
            ++mp[x];

        long long mx = mp.rbegin()->first;
        long long mn = mp.begin()->first;

        if( mx <= mn * (long long)k )
            return 0;

        // int ans = n-1; // worst case: remove all but one element
        // we could do better already: remove all but the most frequent element
        int max_freq = 1;
        int mp_sz = mp.size();
        vector<pair<long,int>> v(mp_sz); // {{val1, count1}, {val2, count2}, ...} sorted by val
        vector<int> prefixSum(mp_sz+1, 0);
        int mp_idx = 0;
        for(auto& p: mp) {
            v[mp_idx] = p;
            max_freq = max(max_freq, p.second);
            prefixSum[mp_idx+1] = prefixSum[mp_idx] + v[mp_idx].second;
            ++mp_idx;
        }

        int ans = n - max_freq;
        if( k == 1 )
            return ans;

        // start removing the smaller elements
        for(int i = 0; i < mp_sz; ++i) { // could also to i < mp_sz-1
            if( mx <= v[i].first * (long long)k )
                break;

            // how many 'small elements' to remove
            // including us
            int a = prefixSum[i+1];

            // how many 'large elements' to remove
            // first element > v[i+1].first * (long long)k
            // aka upper_bound

            int s = i+1;
            long long target = v[i+1].first * (long long)k;
            int t = upper_bound(v, s, target);
            if( t == mp_sz ) {
                // no large elements to remove
                ans = min(ans, a);
                // our loop will break at the next iteration
            } else if( t == s ) {
                // we should never be here
            } else {
                ans = min(ans, a + (n - prefixSum[t]));
            }
        }
        // cout << "best answer after removing small elements " << ans << endl;

        // start removing the larger elements
        for(int i = mp_sz-1; i >= 0; --i) { // could also do i > 0
            if( v[i].first <= mn * (long long)k )
                break;

            // cout << "removing large elements up to and include " << v[i].first << endl;

            // how many 'large elements' to remove
            // including us
            int a = n - prefixSum[i];
            // cout << "  removing total of " << a << " large elements" << endl;

            // how many 'small elements' to remove
            // our max after 'large elements' removal incl. us
            long long cur_max = v[i-1].first; // cout << "  cur_max " << cur_max << endl;
            // find the smallest element in idx range 0...i-2
            // where x * k >= cur_max
            int t = search(v, 0, i-2, k, cur_max);
            // we need to remove elements 0...t-1
            if( t != -1 ) {
                ans = min(ans, a + prefixSum[t]);
            }
        }

        return ans;
    }
};
