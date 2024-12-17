
// 3098. Find the Sum of Subsequence Powers
// https://leetcode.com/problems/find-the-sum-of-subsequence-powers/






class Solution {
private:
    const long mod = 1000000007;

    // long mem[50][51][50][1227];
    // long mem[156442500]
    long mem[50][51][51][2];

    long rec(vector<int>& nums, int n, int pos, int k, int pre, int diff) {
        // diff is our power

        if( k == 0 )
            return (long)diff;

        if( pos == n )
            return 0L;

        // we have choice
        //    don't pick the current pos OR
        //    pick the current pos

        // don't pick
        long ret = rec(nums, n, pos+1, k, pre, diff);

        // pick
        // we may not have picked any yet
        if( pre == -1 ) {
            ret = (ret + rec(nums, n, pos+1, k-1, pos, diff)) % mod;
        } else {
            int diff_new = nums[pos] - nums[pre];
            ret = (ret + rec(nums, n, pos+1, k-1, pos, min(diff, diff_new))) % mod;
        }

        return ret;
    }

    long rec(vector<int>& nums, int n, int pos, int k, int pre, int diff, bool seen) {
        // seen: have we seen this particular diff
        if( k == 0 )
            return seen ? (long)diff : 0L;

        if( pos == n )
            return 0L;

        if( mem[pos][k][pre][seen] != -1 )
          return mem[pos][k][pre][seen];

        // we have choice
        //    don't pick the current pos OR
        //    pick the current pos

        // don't pick
        long ret = rec(nums, n, pos+1, k, pre, diff, seen);

        // pick
        // we may not have picked any yet
        if( pre == n ) {
            ret = (ret + rec(nums, n, pos+1, k-1, pos, diff, seen)) % mod;
        } else {
            int diff_new = nums[pos] - nums[pre];
            bool seen_new = seen;
            if( diff_new == diff )
                seen_new = true;
            if( diff_new >= diff )
                ret = (ret + rec(nums, n, pos+1, k-1, pos, diff, seen_new)) % mod;
        }

        return mem[pos][k][pre][seen] = ret;
    }

public:
    int sumOfPowers(vector<int>& nums, int k) {
        int n = nums.size(); // 2 <= n <= 50; -1e8 <= nums[i] <= 1e8

        // worst case n = 50 and all pairs yield a different difference
        // we can make n * (n-1)/2 pairs
        // n = 50 -> number pairs 1225, so we could have up to 1225 different differences

        // if we sort nums and keep track of the last index we picked,
        // we can determine if our difference gets smaller by doing diff with last picked index
        sort(nums.begin(), nums.end());

        // state would be pos, k, previously picked, diff
        // long mem[50][51][50][1227];
        // long mem[156442500]
        // this is too big
        // return rec(nums, n, 0, k, -1, INT_MAX);

        // what if we check for known 'differences'?
        // as long as we pick at least one pair with that exact difference and no pair with a smaller difference, we are good
        // then our state becomes pos, k, previously picked; and we do that for each difference
        long ans = 0L;
        unordered_set<int> us;
        for(int i = 0; i < n-1; ++i) {
            for(int j = i+1; j < n; ++j) {
                // we are not interested in a diff of 0 because it will not change our sum
                if( nums[j] != nums[i] ) {
                    int diff = nums[j] - nums[i];
                    // have we seen this diff before?
                    if( us.insert(diff).second ) {
                        memset(mem,-1,sizeof mem);
                        long t = rec(nums, n, 0, k, n, diff, false); // pre = n signaling no previous pick
                        ans = (ans + t) % mod;
                    }
                }
            }
        }

        return ans;
    }
};
