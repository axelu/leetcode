
// 3323. Minimize Connected Groups by Inserting Interval
// https://leetcode.com/problems/minimize-connected-groups-by-inserting-interval/





class Solution {
private:
    int geltoet(vector<vector<int>>& nums, int target) {
        // binary search greatest element less than target or equal target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int n = nums.size();

        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid][0] > target )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && nums[s][0] > target) || s == n )
            --s;

        return s;
    }

    int lower_bound(vector<vector<int>>& nums, int target) {
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int n = nums.size();

        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid][0] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s][0] < target )
            ++s;

        return s;
    }

public:
    int minConnectedGroups(vector<vector<int>>& intervals, int k) {
        int n = intervals.size();
        if( n == 1 )
            return 1;

        // interval merge, merge intervals
        sort(begin(intervals),end(intervals));

        int mn = intervals[0][0];
        int mx = intervals[n-1][1];

        vector<vector<int>> r;
        r.push_back(intervals[0]);
        int i = 0;
        for(int j = 1; j < n; ++j) {
            if( intervals[j].front() > r[i].back() ) {
                r.push_back(intervals[j]);
                ++i;
            } else if( intervals[j].front() == r[i].back() ) {
                r[i].back() = intervals[j].back();
            } else if( intervals[j].back() > r[i].back() ) {
                // r[i].front() <= intervals[j].front() < r[i].back()
                r[i].back() = intervals[j].back();
            }
        }
        /*
        for(int i = 0; i < r.size(); ++i)
            cout << r[i][0] << ":" << r[i][1] << " ";
        cout << endl;
        cout << "mn " << mn << endl;
        cout << "mx " << mx << endl;
        */

        // for each interval in r record how many intervals are to its left and to its right
        // from left to right
        // then try each interval end point and find the right most interval that is still touched
        //     record the number of intervals to the left of our starting interval and the
        //     number of intervals to the rightmost interval, record its sum and keep track of minimum
        // from right to left
        // then try each interval starting point and find the leftmost interval that is still touched
        //     record the number of intervals to the right of our starting interval and the
        //     number of intervals to the leftmost interval, records its sum and keep track of minimum

        int r_sz = r.size();
        int ans = r_sz;

        for(int i = 0; i < r_sz; ++i) {
            // cout << "i " << i << " " << r[i][0] << ":" << r[i][1] << endl;
            // number intervals to the left and right of interval i
            int nbrlft = i;
            int nbrrgt = (r_sz - 1) - i;

            // what can we cover from interval iend to the right
            int iend = r[i][1];
            int target = iend + k; // cout << "target right " << target << endl;
            if( target >= mx ) {
                ans = min(ans, nbrlft + 1);
            } else {
                int t = geltoet(r, target); // cout << "t " << t << endl;
                ans = min(ans, nbrlft + 1 + ((r_sz-1) - t));
            }

            // what can we cover from interval istart to the left
            int istart = r[i][0];
            target = istart - k;
            if( target <= mn ) {
                ans = min(ans, 1 + nbrrgt);
            } else {
                int t = lower_bound(r, target);
                ans = min(ans, t + 1 + nbrrgt);
            }
        }

        return ans;
    }
};
