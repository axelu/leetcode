
// 3466. Maximum Coin Collection
// https://leetcode.com/problems/maximum-coin-collection/

class Solution {
private:
    const long long INF = 1e14;
    long long ans;

    long long mem[100001][2];

    long long rec_lane1(vector<int>& lane1, int i) {
        if( i == lane1.size() )
            return 0LL;

        long long ret = max(0LL, lane1[i] + rec_lane1(lane1, i+1));

        ans = max(ans, ret);
        return mem[i][0] = ret;
    }

    long long rec_lane2(vector<int>& lane2, int i) {
        if( i == lane2.size() )
            return 0LL;

        // we have a choice
        //    exit
        //    continue in lane 2
        //    switch to lane 1, which we already populated

        long long ret = max(mem[i][0], (long long)lane2[i] + rec_lane2(lane2, i+1));
        ans = max({ans, 0LL, ret});
        return mem[i][1] = max(0LL, ret);
    }


    long long rec(vector<int>& lane1, vector<int>& lane2, int i, int state) {
        if( i == lane1.size() )
            return 0LL;

        if( mem[i][state] != -1LL )
            return mem[i][state];

        // state = 2: we are on lane 1 and can switch 2 times
        // state = 1: we are on lane 2 and can switch 1 time
        // state = 0: we are on lane 1 and can no longer switch

        // we have a choice
        //    exit
        //    continue on the current lane
        //    switch lanes if we can

        // exit
        long long a = 0LL;

        // continue on the current lane
        long long b = state == 2 || state == 0 ? lane1[i] : lane2[i];
        b += rec(lane1, lane2, i+1, state);

        // switch lanes if we can
        // PROBLEM: we will switch back and forth two times
        // we could grab the current value from the other lane
        // and continue at i+1 in the other lane
        long long c = -INF;
        if( state == 2 || state == 1 ) {
            // c = rec(lane1, lane2, i, state-1);
            c = state == 2 ? lane2[i] : lane1[i];
            c += rec(lane1, lane2, i+1, state-1);
        }
        
        long long ret = max({a,b,c});

        // we can enter the highway at any point
        ans = max(ans, ret);

        return mem[i][state] = ret;
    }

    long long rec(vector<int>& lane1, int i) {
        if( i == lane1.size() )
            return 0LL;

        // we have a choice
        //     exit
        //     continue in lane1
        //     switch to lane1 with one switch left, which we have already explored

        long long ret = max(mem[i][1], (long long)lane1[i] + rec(lane1, i+1));
        ans = max({ans, 0LL, ret});
        return max(0LL, ret);
    }

public:
    long long maxCoins(vector<int>& lane1, vector<int>& lane2) {
        int n = lane1.size(); // lane1.size() == lane2.size()

        // must ride on the freeway for at least one mile
        // if all tolls are non-positive, our largest number is the answer
        int mx = *max_element(begin(lane1), end(lane1));
        mx = max(mx, *max_element(begin(lane2), end(lane2)));

        ans = -INF;

        memset(mem,-1,sizeof mem);
        rec_lane1(lane1, 0); // stay in lane 1 the whole time
        rec_lane2(lane2, 0);
        rec(lane1, 0);

        if( ans == 0 && mx < 0 )
            return mx;
        
        return ans;
    }
};


// passes 854/858 test cases, then TLE as of 2/25/2025
// case 855 runs in about 2500ms delivering correct result, but that is
// obviously too slow

class Solution {
private:
    const long long INF = 1e14;
    long long ans;

    long long mem[100001][3];

    long long rec(vector<int>& lane1, vector<int>& lane2, int i, int state) {
        int n = lane1.size(); // lane1.size() == lane2.size()
        if( i == n )
            return 0LL;

        if( mem[i][state] != -1LL )
            return mem[i][state];

        // state = 2: we are on lane 1 and can switch 2 times
        // state = 1: we are on lane 2 and can switch 1 time
        // state = 0: we are on lane 1 and can no longer switch

        // we have a choice
        //    exit
        //    continue on the current lane
        //    switch lanes if we can

        // exit
        long long a = 0LL;

        // continue on the current lane
        long long b = state == 2 || state == 0 ? lane1[i] : lane2[i];
        b += rec(lane1, lane2, i+1, state);

        // switch lanes if we can
        // PROBLEM: we will switch back and forth two times
        // we could grab the current value from the other lane
        // and continue at i+1 in the other lane
        long long c = -INF;
        if( state == 2 || state == 1 ) {
            // c = rec(lane1, lane2, i, state-1);
            c = state == 2 ? lane2[i] : lane1[i];
            c += rec(lane1, lane2, i+1, state-1);
        }

        long long ret = max({a,b,c});

        // we can enter the highway at any point
        if( state == 2 )
            ans = max(ans, ret);

        return mem[i][state] = ret;
    }

public:
    long long maxCoins(vector<int>& lane1, vector<int>& lane2) {
        int n = lane1.size(); // lane1.size() == lane2.size()

        // must ride on the freeway for at least one mile
        // if all tolls are non-positive, our largest number is the answer
        int mx = *max_element(begin(lane1), end(lane1));
        mx = max(mx, *max_element(begin(lane2), end(lane2)));

        ans = -INF;

        memset(mem,-1,sizeof mem);
        ans = max(ans, rec(lane1, lane2, 0, 2));

        if( ans == 0 && mx < 0 )
            return mx;

        return ans;
    }
};
