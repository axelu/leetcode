
// 3404. Count Special Subsequences
// https://leetcode.com/problems/count-special-subsequences/

class Solution {
public:
    long long numberOfSubsequences(vector<int>& nums) {
        int n = nums.size();

        long long ans = 0LL;

        // [0 or more]p[1 or more]q[1or more]r[1or more]s[0 or more]
        //            p           q          r          s
        // nums[p] * nums[r] == nums[q] * nums[s] <- that is our condition
        // rewritten to get indicies in order aka indicies on the same site of the equation
        // so that we can split the array in our investigation
        // nums[p] / nums[q] == nums[s] / nums[r]
        // Note: for ratios we could store and compare result using double OR
        //       we can use GCD
        //
        // 01234567890123456789
        // p q r s              start
        //              p q r s
        // let us fix r and q and move left to right

        long long cnt[1001][1001];memset(cnt,0,sizeof cnt);

        for(int r = 4; r < n-2; ++r) {
            int q = r-2;

            for(int p = 0; p < q-1; ++p) {
                int _gcd = gcd(nums[p], nums[q]);
                ++cnt[nums[p]/_gcd][nums[q]/_gcd];
            }
            for(int s = r+2; s < n; ++s) {
                int _gcd = gcd(nums[s], nums[r]);
                ans += cnt[nums[s]/_gcd][nums[r]/_gcd];
            }
        }

        return ans;
    }
};


// passes 556/557 test cases as of 12/30/2024, then TLE
// test case 557 delivers correct result, runs in about 445ms

class Solution {
public:
    long long numberOfSubsequences(vector<int>& nums) {
        int n = nums.size();

        long long ans = 0LL;

        long long s[1000001];memset(s,0,sizeof s);
        for(int r = n-3; r >= 4; --r) {
            ++s[nums[r+2]];

            for(int p = r-4; p >= 0; --p) {
                int pxr = nums[p] * nums[r];

                for(int q = p+2; q <= r-2; ++q) {
                    if( pxr % nums[q] )
                        continue;
                    ans += s[pxr / nums[q]];
                }
            }
        }

        return ans;
    }
};
