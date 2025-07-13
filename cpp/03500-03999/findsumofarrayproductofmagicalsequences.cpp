
// 3539. Find Sum of Array Product of Magical Sequences
// https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/




// I could not figure out the carry mask concept on my own, hence had to look at other solutions
// credits to
// https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/solutions/6715198/hopeless-brute-force-dp-states-pruning-bitmasking
// https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/solutions/6713399/detailed-explain-50lines-c-solution-group-numbers-sets-bitmask-top-down-dp


// initialize once
// modular combinations precompuate via Pascal's triangle
bool init = false;
long nCk[31][31];


class Solution {
private:

    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    const long mod = 1000000007;

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

        return ret % mod;
    }

    int mem[50][31][31][16];

    long rec(vector<int>& nums, int n, int i, int m, int k, int mask) {
        if( m < 0 || k < 0 || m + countSetBits(mask) < k )
            return 0L;

        if( m == 0 )
            return countSetBits(mask) == k ? 1L : 0L;

        if( i == n )
            return 0L;

        if( mem[i][m][k][mask] != -1)
            return mem[i][m][k][mask];

        long ret = 0;

        for(int c = 0; c <= m; ++c) {
            // number of ways to choose positions * nums[i]^c
            long f = (nCk[m][c] * modular_pow(nums[i], c)) % mod;

            // update carry mask
            int mask_new  = mask + c;
            int mask_next = mask_new >> 1; // division by 2

            int bit_contribution = mask_new & 1;

            ret = (ret + f * rec(nums, n, i+1, m-c, k-bit_contribution, mask_next)) % mod;
        }

        return mem[i][m][k][mask] = ret;
    }

public:
    int magicalSum(int m, int k, vector<int>& nums) {
        // constraints
        //     1 <= k <= m <= 30
        //     1 <= nums.length <= 50
        //     1 <= nums[i] <= 1e8

        if( !init ) {
            init = true;

            for(int i = 0; i <= 30; ++i) {
                nCk[i][0] = 1;
                nCk[i][i] = 1;
            }
            for(int i = 2; i <= 30; ++i) {
                for(int j = 1; j < 30; ++j) {
                    nCk[i][j] = (nCk[i-1][j] + nCk[i-1][j-1]) % mod;
                }
            }
        }

        int n = nums.size();

        memset(mem,-1,sizeof mem);
        return rec(nums, n, 0, m, k, 0);
    }
};
