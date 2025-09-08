
// 3654. Minimum Sum After Divisible Sum Deletions
// https://leetcode.com/problems/minimum-sum-after-divisible-sum-deletions/


class Solution {
private:
    int remainder[100000];
    long prefixSum[100001];
    int remainder_prefixSum[100001];
    set<int> mp[100000]; // key: remainder_prefixSum value: indices at which key occurs

    long long mem[100000];

    long long rec(vector<int>& nums, int n, int pos) {
        if( pos == n )
            return 0LL;

        if( mem[pos] != -1LL )
            return mem[pos];

        // we have a choice
        //      don't take OR
        //      take, meaning continue at next occurence of remainder_prefixSum

        long long ret = (long long)nums[pos] + rec(nums, n, pos+1);

        // where do we continue?
        int rem = remainder_prefixSum[pos];
        auto it = mp[rem].find(pos); // it is guaranteed that pos is in mp[rem] set
        if( next(it) != mp[rem].end() ) {
            // we can continue at *(next(it)) pos, which would be our r
            int r = *(next(it));
            // the array pos ... r-1 can be collapsed
            ret = min(ret, rec(nums, n, r));
        }

        return mem[pos] = ret;
    }
    
public:
    long long minArraySum(vector<int>& nums, int k) {
        if( k == 1 )
            return 0LL;
        
        int n = nums.size(); // 1 <= nums.length <= 1e5


        /*                      0 1 2 3 4 5 6
            example             2 3 1 4 1 5    n = 6, k = 3
            remainder           2 0 1 1 1 2
            prefixSum_remainder 0 2 2 3 4 5 7
            remainder_prefixSum 0 2 2 0 1 2 1
            when we are at a given remainder_prefixSum, let pos be l, the next
            occurence of same remainder_prefixSum marks the position, let pos be r
            at which we could continue, and array l ... r-1 can be deleted
            examples from above l = 0 r = 3 or
                                l = 1 r = 2,5 and so on 
         */

        // remainder
        // vector<int> remainder(n);
        for(int i = 0; i < n; ++i)
            remainder[i] = nums[i] % k;
        
        // prefixSum_remainder
        // vector<long> prefixSum(n+1);
        prefixSum[0] = 0L;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + (long)remainder[i-1];
        
        // remainder_prefixSum
        // vector<int> remainder_prefixSum(n+1);
        for(int i = 0; i <= n; ++i)
            remainder_prefixSum[i] = prefixSum[i] % (long)k;

        // map<int,set<int>> mp; // key: remainder_prefixSum value: indices at which key occurs
        for(int i = 0; i <= n; ++i)
            mp[remainder_prefixSum[i]].insert(i);

        memset(mem, -1, sizeof mem);
        return rec(nums, n, 0);
    }
};


// passes 820/844 test casess as of 8/30/2025, then TLE
// case 821 runs in ~539ms returning correct result, but obviously too slow

class Solution {
private:
    long long mem[100000];

    long long rec(vector<int>& nums, int n, int pos, vector<int>& remainder_prefixSum, map<int,set<int>>& mp) {
        if( pos == n )
            return 0LL;

        if( mem[pos] != -1LL )
            return mem[pos];

        // we have a choice
        //      don't take OR
        //      take, meaning continue at next occurence of remainder_prefixSum

        long long ret = (long long)nums[pos] + rec(nums, n, pos+1, remainder_prefixSum, mp);

        // where do we continue?
        int rem = remainder_prefixSum[pos];
        auto it = mp[rem].find(pos); // it is guaranteed that pos is in mp[rem] set
        if( next(it) != mp[rem].end() ) {
            // we can continue at *(next(it)) pos, which would be our r
            int r = *(next(it));
            // the array pos ... r-1 can be collapsed
            ret = min(ret, rec(nums, n, r, remainder_prefixSum, mp));
        }

        return mem[pos] = ret;
    }

public:
    long long minArraySum(vector<int>& nums, int k) {
        if( k == 1 )
            return 0LL;

        int n = nums.size(); // 1 <= nums.length <= 1e5


        /*                      0 1 2 3 4 5 6
            example             2 3 1 4 1 5    n = 6, k = 3
            remainder           2 0 1 1 1 2
            prefixSum_remainder 0 2 2 3 4 5 7
            remainder_prefixSum 0 2 2 0 1 2 1
            when we are at a given remainder_prefixSum, let pos be l, the next
            occurence of same remainder_prefixSum marks the position, let pos be r
            at which we could continue, and array l ... r-1 can be deleted
            examples from above l = 0 r = 3 or
                                l = 1 r = 2,5 and so on
         */

        // remainder
        vector<int> remainder(n);
        for(int i = 0; i < n; ++i)
            remainder[i] = nums[i] % k;

        // prefixSum_remainder
        vector<long> prefixSum(n+1);
        prefixSum[0] = 0L;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + (long)remainder[i-1];

        // remainder_prefixSum
        vector<int> remainder_prefixSum(n+1);
        for(int i = 0; i <= n; ++i)
            remainder_prefixSum[i] = prefixSum[i] % (long)k;

        map<int,set<int>> mp; // key: remainder_prefixSum value: indices at which key occurs
        for(int i = 0; i <= n; ++i)
            mp[remainder_prefixSum[i]].insert(i);

        memset(mem, -1, sizeof mem);
        return rec(nums, n, 0, remainder_prefixSum, mp);
    }
};
