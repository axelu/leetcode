
// 3639. Minimum Time to Activate String
// https://leetcode.com/problems/minimum-time-to-activate-string/





class Solution {
public:
    int minTime(string s, vector<int>& order, int k) {
        int n = s.size(); // 1 <= n <= 1e5; s.size() == order.size()
        // if we would replace all positions in s with with *
        // what is the max number of valid substrings that can be formed?
        // = number of subarrays
        // formula of number of non-empty subarrays n * ((n+1)/2)
        // worst case n = 1e5 => 5000050000 possible subarrays
        // INT_MAX               2147483647
        long long max_subarrays = (long long)n * (n+1)/2.0; // cout << "max_subarrays " << max_subarrays << endl;
        if( (long long)k > max_subarrays )
            return -1;
        if( (long long)k == max_subarrays )
            return n-1;

        // we can make valid substrings that 'pivot' around
        // every position where we have a *, but don't double count
        // note it does not matter what chars, only the *'s matter

        // initially we can make as many invalid subarrays
        // as there are possible subarrays
        // at every time point we split or shrink an existing
        // range that allowed us to make invalid subarrays
        long long total_invalid = max_subarrays;
        vector<array<int,2>> intervals{{0, n-1}};
        for(int t = 0; t < n; ++t) {
            int idx = order[t];

            // find the interval that we are splitting or shrinking
            // TODO make this faster with like binary search
            int i = 0;
            for(; i < intervals.size(); ++i) {
                if( intervals[i][0] <= idx && idx <= intervals[i][1] )
                    break;
            }

            // we are splitting or shrinking the interval i
            // how many invalid substrings does interval i contribute?
            long long l = intervals[i][1] - intervals[i][0] + 1;
            long long invalid = l * (l+1LL)/2.0;
            total_invalid -= invalid;

            // are we shrinking or splitting?
            if( idx == intervals[i][0] && idx == intervals[i][1] ) {
                // we are erasing aka shrinking to a length of zero
                auto it = intervals.begin();
                advance(it, i);
                intervals.erase(it);
                invalid = 0LL;

            } else if( idx == intervals[i][0] ) {
                // we are shrinking
                ++intervals[i][0];
                --l;
                invalid = l * (l+1LL)/2.0;

            } else if( idx == intervals[i][1] ) {
                // we are shrinking
                --intervals[i][1];
                --l;
                invalid = l * (l+1LL)/2.0;

            } else {
                // we are splitting
                auto it = intervals.begin();
                advance(it, i);

                // new interval
                int s = intervals[i][0];
                int e = idx-1;
                long long l0 = e - s + 1;
                invalid = l0 * (l0+1LL)/2.0;

                // update existing interval
                intervals[i][0] = idx+1;
                long long l1 = intervals[i][1] - intervals[i][0] + 1;
                invalid += l1 * (l1+1LL)/2.0;

                // insert new interval
                intervals.insert(it, {s,e});
            }

            total_invalid += invalid;
            if( max_subarrays - total_invalid >= k )
                return t;
        }


        return n-1; // we should never get here
    }
};
