
// 2518. Number of Great Partitions
// https://leetcode.com/problems/number-of-great-partitions/



class Solution {
private:
    long mod = 1000000007;

    // exponention using bit manipulation
    long modular_pow(long base, long exponent) {

        long ret = 1;

        while(exponent > 0) {

            int last_bit = (exponent & 1);
            if( last_bit )
                ret = (ret * base) % mod;

            base = (base * base) % mod;

            exponent = exponent >> 1;
        }

        return ret;
    }

    int mem[1000][1000];

    long rec(vector<int>& nums, int n, int pos, int sum, int k) {
        if( pos == n || nums[pos] >= k || sum + nums[pos] >= k )
            return 0L;

        if( mem[pos][sum] != -1 )
            return mem[pos][sum];

        // we have a choice
        //    don't pick the current element OR
        //    pick the current element

        long ret = rec(nums,n,pos+1,sum,k);

        ret = (ret + (1L + rec(nums,n,pos+1,sum+nums[pos],k))) % mod;

        return mem[pos][sum] = ret;
    }

public:
    int countPartitions(vector<int>& nums, int k) {
        int n = nums.size();
        if( n == 1 )
            return 0;

        // rephrasing the problem
        // find all subsequences of length [1,n-1] inclusive
        // who's sum >= k and sum <= (sum nums) - k
        // that also means that sum nums has to be >= 2*k

        long total = 0L;
        int mn = INT_MAX;
        for(int x: nums) {
            total += (long)x;
            mn = min(mn,x);
        }

        if( total < 2L * k )
            return 0;

        // if all elements where >= k, we could make 2^n partitions
        // minus 1 for the case of no elements selected for any partition and
        // minus 1 for the case of all elements selected for one partition
        // let the two partitions be 0 and 1
        // example nums = {1,2,3,4,}, k = 4
        //      sum nums = 1+2+3+4 = 10
        //                 0 0 0 0 sum partition 0 = 10, sum partition 1 =  4 -> invalid
        //                 0 0 0 1 sum partition 0 =  6, sum partition 1 =  4 -> valid
        //                 0 0 1 0 sum partition 0 =  7, sum partition 1 =  3 -> invalid
        //                 0 0 1 1 sum partition 0 =  3, sum partition 1 =  7 -> invalid
        //                 0 1 0 0 sum partition 0 =  8, sum partition 1 =  2 -> invalid
        //                 0 1 0 1 sum partition 0 =  4, sum partition 1 =  6 -> valid
        //                 0 1 1 0 sum partition 0 =  5, sum partition 1 =  5 -> valid
        //                 0 1 1 1 sum partition 0 =  1, sum partition 1 =  9 -> invalid
        //                 1 0 0 0 sum partition 0 =  9, sum partition 1 =  1 -> invalid
        //                 1 0 0 1 sum partition 0 =  5, sum partition 1 =  5 -> valid
        //                 1 0 1 0 sum partition 0 =  6, sum partition 1 =  4 -> valid
        //                 1 0 1 1 sum partition 0 =  2, sum partition 1 =  8 -> invalid
        //                 1 1 0 0 sum partition 0 =  7, sum partition 1 =  3 -> invalid
        //                 1 1 0 1 sum partition 0 =  3, sum partition 1 =  7 -> invalid
        //                 1 1 1 0 sum partition 0 =  4, sum partition 1 =  6 -> valid
        //                 1 1 1 1 sum partition 0 =  0, sum partition 1 = 10 -> invalid
        //      ans 6 valid parititions

        if( mn >= k )
            return modular_pow(2,n) - 2; // -2 subtract 0 and subtract all

        sort(nums.begin(),nums.end());
        memset(mem,-1,sizeof mem);
        // number of invalid paritions 'for parition 1'
        // * 2 because the same applies if those would be selected for parition 0
        long t = (rec(nums,n,0,0,k) * 2L) % mod;

        long ans = modular_pow(2,n) - 2 - t;
        if( ans < 0 )
            ans += mod;

        return ans;
    }
};
