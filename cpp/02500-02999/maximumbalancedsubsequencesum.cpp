
// 2926. Maximum Balanced Subsequence Sum
// https://leetcode.com/problems/maximum-balanced-subsequence-sum/




class Solution {
private:
    long long rec(vector<int> nums, int n, int pos, long long mem[]) {
        // if we come to a position, we know we can take it

        if( mem[pos] != -1 )
            return mem[pos];

        long long ret = nums[pos];

        for(int i = pos+1; i < n; ++i) {

            int r = i - pos;
            int l = nums[i] - nums[pos];

            if( l >= r ) {
                long long t = nums[pos] + rec(nums, n, i, mem);
                ret = max(ret, t);
            }
        }

        return mem[pos] = ret;
    }

    long long t[200002]; // segment tree memory efficient indexing, max, max range query, pos update

    long long get_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return max(get_max(v+1, tl, tm, l, min(r, tm)),
                   get_max(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r));
    }

    long long get(int v, int tl, int tr, int pos) {
        if (tl == tr) {
            return t[v];
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                return get(v+1, tl, tm, pos);
            else
                return get(v+2*(tm-tl+1), tm+1, tr, pos);
        }
    }

    void update(int v, int tl, int tr, int pos, long long new_val) {
        if (tl == tr) {
            t[v] = new_val;
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
    long long maxBalancedSubsequenceSum(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 100000
        if( n == 1 )
            return (long long)nums[0];


        /*
        // top down with memoization
        // correct, but too slow given n
        long long ans = LLONG_MIN;
        long long mem[100000];
        memset(mem,-1,sizeof mem);
        for(int i = 0; i < n; ++i)
            ans = max(ans, rec(nums, n, i, mem));
        // the slowness comes from us at each position
        // having to look at any position behind us
        */

        // solution based on hints given in the problem

        // -1e9 <= nums[i] <= 1e9
        // that is a wide range, but we only have max 100000 different values
        // due to nmax = 100000
        // so we can use a map to limit our range
        set<int> st;
        for(int i = 0; i < n; ++i)
            st.insert(nums[i] - i);
        int idx = 0;
        map<int,int> dict;
        for(int key: st)
            if( dict.insert({key, idx}).second )
                ++idx;

        // our original condition nums[x] - nums[y] >= x - y where x > y
        // rewritten as           nums[x] - x       >= nums[y] - y
        // let dp[x] be the maximum sum of a balanced subsequence ending at index x
        long long dp[100000];
        // going from left to right
        // at some index x, we need to find an index y, where y < x, and
        //     dp[x] = nums[x] + dp[y] is maximized and nums[x] - x >= nums[y] - y
        // going left to right, if we are at x, we only have processed indicies smaller than x

        // our segment tree will hold dp[x] basically
        // init tree to all 0
        memset(t,0,sizeof t);

        // dict[nums[x] - x] represents the position of the value, nums[x] - x, in the segment tree
        int tr = dict.size() - 1;
        for(int x = 0; x < n; ++x) {

            int r, pos;
            r = pos = dict[nums[x] - x];

            dp[x] = max((long long)nums[x], (long long)nums[x] + get_max(1, 0, tr, 0, r));

            if( dp[x] > get(1, 0, tr, pos) )
                update(1, 0, tr, pos, dp[x]);
        }

        long long ans = LLONG_MIN;
        for(int x = 0; x < n; ++x)
            ans = max(ans, dp[x]);

        return ans;
    }
};
