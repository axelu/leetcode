

// 2572. Count the Number of Square-Free Subsets
// https://leetcode.com/problems/count-the-number-of-square-free-subsets/



/* constraints
 *     1 <= nums.length <= 1000
 *     1 <= nums[i] <= 30
 *     largest product 30^1000
 *  we cannot have any sqare number <= 30 other than 1 as part of the subset
 * square numbers between [1,30] inclusive:
 *  1 = 1*1
 *  4 = 2*2
 *  9 = 3*3
 * 16 = 4*4
 * 25 = 5*5
 * we cannot have 2 the same numbers as part of the subset
 * in fact, if we have a number and do a prime factorization,
 * we cannot add any number that byitself has a prime multiple times byitself,
 * example 27 = 3 * 3 * 3
 * additionally, if we have a number like 15 with primefactors 3 and 5,
 * we cannot add a number to the subset that has 3 or 5 in its primefactors
 *
 * there are 10 primes below 30
 * bit     9  8  7  6  5  4  3  2  1  0
 * primes 29 23 19 17 13 11  7  5  3  2
 *                                                                       unique prime  unique prime
 *                                                                       factors mask  factors mask
 *                                                                       binary        decimal
 *  1
 *  2 prime                                                              0000000001       1
 *  3 prime                                                              0000000010       2
 *  4 = 2 * 2 square number                  cannot be part of a subset
 *  5 prime                                                              0000000100       4
 *  6 = 2 * 3                                                            0000000011       3
 *  7 prime                                                              0000001000       8
 *  8 = 2 * 2 * 2                           cannot be part of a subset
 *  9 = 3 * 3 square number                 cannot be part of a subset
 * 10 = 2 * 5                                                            0000000101       5
 * 11 prime                                                              0000010000      16
 * 12 = 2 * 2 * 3                           cannot be part of a subset
 * 13 prime                                                              0000100000      32
 * 14 = 2 * 7                                                            0000001001       9
 * 15 = 3 * 5                                                            0000000110       6
 * 16 = 4 * 4 square number = 2 * 2 * 2 * 2 cannot be part of a subset
 * 17 prime                                                              0001000000      64
 * 18 = 2 * 3 * 3                           cannot be part of a subset
 * 19 prime                                                              0010000000     128
 * 20 = 2 * 2 * 5                           cannot be part of a subset
 * 21 = 3 * 7                                                            0000001010      10
 * 22 = 2 * 11                                                           0000010001      17
 * 23 prime                                                              0100000000     256
 * 24 = 2 * 2 * 2 * 3                       cannot be part of a subset
 * 25 = 5 * 5 square number                 cannot be part of a subset
 * 26 = 2 * 13                                                           0000100001      33
 * 27 = 3 * 3 * 3                           cannot be part of a subset
 * 28 = 2 * 2 * 7                           cannot be part of a subset
 * 29 prime                                                              1000000000     512
 * 30 = 2 * 3 * 5                                                        0000000111       7
 */
class Solution {
private:
    long mod = 1000000007;
    // unique prime factor masks decimal, see above
    int upfm[31] = {0,0,1,2,0,4,3,8,0,0,5,16,0,32,9,6,0,64,0,128,0,10,17,256,0,0,33,0,0,512,7};

    int modular_pow(unsigned long long base, int exponent) {
        unsigned long long c = 1;
        for(int i = 0; i < exponent; ++i)
            c = (c * base) % mod;
        return c;
    }

    long rec(vector<int>& nums, int n, int i, int mask, long mem[][1024]) {
        // cout << "rec i " << i << " mask " << mask << endl;
        if( i == n )
            return mask != 0 ? 1 : 0;

        if( mem[i][mask] != -1 )
            return mem[i][mask];

        // we have a choice
        //    don't add the current nums[i] to the set OR
        //    add the current nums[i] to the set if we can

        long ret = rec(nums,n,i+1,mask,mem);

        if( (upfm[nums[i]] & mask) == 0 )
            ret = (ret + rec(nums,n,i+1,upfm[nums[i]]|mask,mem)) % mod;

        return mem[i][mask] = ret;
    }
public:
    int squareFreeSubsets(vector<int>& nums) {
        int n_org = nums.size();

        // count 1's in nums and remove them if any
        // remove all numbers that cannot be part of a subset byitself, if any
        int ones = 0;
        vector<int> arr;
        for(int x: nums) {
            if( x == 1 ) {
                ++ones;
                continue;
            } else if( upfm[x] == 0 ) {
                continue;
            }
            arr.push_back(x);
        }
        int n = arr.size();

        // number of subsets we can make using all 1s in nums
        long onesf = modular_pow(2,ones) - 1;
        if( n_org == ones || n == 0 )
            return onesf;

        // number of subsets we can make using all other 'good' numbers
        long mem[n][1024];memset(mem,-1,sizeof mem);
        long others = rec(arr,n,0,0,mem);

        // return others + onesf + others * onesf;
        return (((others + onesf) % mod) + ((others * onesf) % mod)) % mod;
    }
};
