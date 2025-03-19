
// 3414. Maximum Score of Non-overlapping Intervals
// https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/

class Solution {
private:
    // binary search
    int search(vector<vector<int>>& nums, int n, int target) {
        // binary search greatest element less than target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid][1] < target )
                s = mid+1;
            else
                e = mid;
        }
        if( (s < n && nums[s][1] >= target) || s == n )
            --s;

        return s;
    }

    bool cmp(vector<int>& a, vector<int>& b) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int a_sz = a.size();
        int b_sz = b.size();
        for(int i = 0; i < min(a_sz,b_sz); ++i)
            if( a[i] != b[i] )
                return a[i] < b[i];

        return a_sz < b_sz;
    }

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // intervals = {{l, r, weight},...}

        // add index intervals = {{l, r, weight, index},...}

        for(int i = 0; i < n; ++i)
            intervals[i].push_back(i);

        sort(begin(intervals), end(intervals), [](const vector<int>& a, const vector<int>& b){
            if ( a[1] < b[1] ) {
                return true;
            } else if( a[1] == b[1] ) {
                if( a[0] > b[0] ) {
                    return true;
                }
            }
            return false;
        });
        /*
        for(auto interval: intervals)
            cout << interval[0] << "," << interval[1] << "," << interval[2] << "," << interval[3] << " ";
        cout << endl;
        */


        long dp[50000][5];
        vector<int> dp_indices[50000][5];
        // pick 1
        dp[0][1] = intervals[0][2];
        dp_indices[0][1] = {intervals[0][3]};
        for(int i = 1; i < n; ++i) {
            // dp[i][1] = max(dp[i-1][1], (long)intervals[i][2]);
            if( dp[i-1][1] > (long)intervals[i][2] ) {
                dp[i][1] = dp[i-1][1];
                dp_indices[i][1] = dp_indices[i-1][1];
            } else if( dp[i-1][1] == (long)intervals[i][2] ) {
                dp[i][1] = dp[i-1][1];
                if( dp_indices[i-1][1][0] < intervals[i][3] )
                    dp_indices[i][1] = dp_indices[i-1][1];
                else
                    dp_indices[i][1] = {intervals[i][3]};
            } else { // dp[i-1][1] < (long)intervals[i][2]
                dp[i][1] = (long)intervals[i][2];
                dp_indices[i][1] = {intervals[i][3]};
            }
        }
        /*
        cout << "pick 1 max " << dp[n-1][1]  << ": ";
        for(int x: dp_indices[n-1][1] )
            cout << x << " ";
        cout << endl;
        */

        // pick 2, 3, 4
        dp[0][2] = -1;
        dp[0][3] = -1;
        dp[1][3] = -1;
        dp[0][4] = -1;
        dp[1][4] = -1;
        dp[2][4] = -1;
        for(int k = 2; k <= 4; ++k) {
            for(int i = 1; i < n; ++i) {
                // largest to continue from
                int t = search(intervals, i, intervals[i][0]);
                if( t == -1 ) {
                    dp[i][k] = dp[i-1][k]; // -1;
                    dp_indices[i][k] = dp_indices[i-1][k];
                    continue;
                }
                // dp[i][2] = max(dp[i-1][2], (long)intervals[i][2] + dp[t][1]);
                if( dp[i-1][k] > (long)intervals[i][2] + dp[t][k-1] ) {
                    dp[i][k] = dp[i-1][k];
                    dp_indices[i][k] = dp_indices[i-1][k];
                } else if( dp[i-1][k] == (long)intervals[i][2] + dp[t][k-1] ) {
                    dp[i][k] = dp[i-1][k];
                    vector<int> b = dp_indices[t][k-1];
                    b.push_back(intervals[i][3]);
                    if( cmp(dp_indices[i-1][k], b) )
                        dp_indices[i][k] = dp_indices[i-1][k];
                    else
                        dp_indices[i][k] = b;
                } else { // dp[i-1][1] < (long)intervals[i][2] + dp[t][1]
                    dp[i][k] = (long)intervals[i][2] + dp[t][k-1];
                    vector<int> b = dp_indices[t][k-1];
                    b.push_back(intervals[i][3]);
                    dp_indices[i][k] = b;
                }

            }
        }
        /*
        cout << "pick 2 max " << dp[n-1][2] << ": ";
        for(int x: dp_indices[n-1][2] )
            cout << x << " ";
        cout << endl;
        cout << "pick 3 max " << dp[n-1][3] << ": ";
        for(int x: dp_indices[n-1][3] )
            cout << x << " ";
        cout << endl;
        cout << "pick 4 max " << dp[n-1][4] << ": ";
        for(int x: dp_indices[n-1][4] )
            cout << x << " ";
        cout << endl;
        */

        vector<int> ans = dp_indices[n-1][1];
        long mx = dp[n-1][1];
        for(int k = 2; k <= 4; ++k) {       
            if( dp[n-1][k] > mx ) {
                mx = dp[n-1][k];
                ans = dp_indices[n-1][k];
            } else if( dp[n-1][k] == mx ) {
                if( cmp(dp_indices[n-1][k], ans) )
                    ans = dp_indices[n-1][k];
            }
        }

        sort(begin(ans), end(ans));
        return ans;
    }
};


// passes 579/580 test cases as of 1/14/2025, then TLE
// case 580 runs in about 400ms


class Solution {
private:

    // binary search
    int search(vector<vector<int>>& nums, int s, int target) {
        // TODO we can cache result by target
        // if we checked before, return max(s, prior answer)

        int n = nums.size();
        if( s == n )
            return n;

        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target -> s in our case
        // binary search upper bound while loop
        // upper bound -> greater than target
        // int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= nums[mid][0] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && nums[s][0] <= target )
            ++s;

        return s;
    }

    bool cmp(vector<long>& a, vector<long>& b) {
        if( a[0] > b[0] )
            return true;
        if( a[0] < b[0] )
            return false;

        // a[0] == b[0] aka score is the same
        // score cannot be the same and be 0, meaning both have at least picked one element
        sort(next(a.begin()), a.end());
        sort(next(b.begin()), b.end());

        int a_sz = a.size();
        int b_sz = b.size();
        for(int i = 1; i < min(a_sz,b_sz); ++i)
            if( a[i] != b[i] )
                return a[i] < b[i];

        return a_sz < b_sz;
    }

    vector<long> mem[50000][5];

    vector<long> rec(vector<vector<int>>& intervals, int pos, int k) {
        // return 0 = score, rest are indicies


        if( k == 0 )
            return {0};
        int n = intervals.size();
        if( pos == n )
            return {0};

        if( !mem[pos][k].empty() )
            return mem[pos][k];

        // when we arrive at a certain index, we know we can pick it
        // we have a choice
        //    don't pick the current index OR
        //    pick the current index

        auto a = rec(intervals, pos+1, k);

        // where can we continue?
        int nxt = search(intervals, pos+1, intervals[pos][1]);
        auto t = rec(intervals, nxt, k-1);
        vector<long> b = {(long)intervals[pos][2]+t[0], intervals[pos][3]};
        for(int i = 1; i < t.size(); ++i)
            b.push_back(t[i]);

        bool f = cmp(a, b);
        return mem[pos][k] = f ? a : b;
    }

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // intervals = {{l, r, weight},...}

        // add index intervals = {{l, r, weight, index},...}
        for(int i = 0; i < n; ++i)
            intervals[i].push_back(i);

        sort(begin(intervals), end(intervals), [](const vector<int>& a, const vector<int>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) {
                    return true;
                }
            }
            return false;
        });
        /*
        for(auto interval: intervals)
            cout << interval[0] << "," << interval[1] << "," << interval[2] << "," << interval[3] << " ";
        cout << endl;
        */

        auto res = rec(intervals, 0, 4);

        vector<int> ans;
        for(int i = 1; i < res.size(); ++i)
            ans.push_back(res[i]);
        sort(begin(ans), end(ans));
        return ans;
    }
};
