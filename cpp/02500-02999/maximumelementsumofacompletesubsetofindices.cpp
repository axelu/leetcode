
// 2862. Maximum Element-Sum of a Complete Subset of Indices
// https://leetcode.com/problems/maximum-element-sum-of-a-complete-subset-of-indices/






/* perfect square definition:
 * A perfect square is a number that can be expressed as the product of an integer by itself.
 * like 4 = 2*2, 9 = 3*3, 16 = 4*4, and so on.
 * perfect sqares have an even number of each of their prime factors
 * hence we can group numbers aka indicies, if they for a given prime factor, have an odd number of said prime factor
 * example 2 and 8
 *    2 prime factors: 2
 *    8 prime factors: 2 2 2
 *    -> 2 * 8 = 16, 15 prime factors 2 2 2 2
 * example 3 and 12
 *    3 prime factors: 3
 *   12 prime factors: 2 2 3
 *   -> 3 * 12 = 36, 36 prime factors 2 2 3 3
 * example 4 and 9:
 *    4 prime factors: 2 2
 *    9 prime factors: 3 3
 *    -> 4 * 9 = 36: 36 prime factors 2 2 3 3
 */
class Solution {
private:
    // prime factorization
    unordered_map<int,int> primeFactors(int n) {
        unordered_map<int,int> ret;

        // the number of 2s that divide n
        while(n % 2 == 0) {
            // cout << 2 << " ";
            ++ret[2];
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(int i = 3; i <= sqrt(n); i = i + 2) {
            while(n % i == 0) {
                // cout << i << " ";
                ++ret[i];
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2 ) {
            // cout << n << " ";
            ++ret[n];
        }

        return ret;
    }

    unordered_map<int,vector<int>> group_indicies(int n) {
        unordered_map<int,vector<int>> groups;

        for(int i = 1; i <= n; ++i) {
            auto um = primeFactors(i);

            int f = 1;
            for(auto it = um.begin(); it != um.end(); ++it) {
                if( it->second % 2 == 1 )
                    f *= it->first;
            }

            groups[f].push_back(i);
        }

        return groups;
    }



public:
    long long maximumSum(vector<int>& nums) {
        int n = nums.size(); // 1 <= n == nums.length <= 10^4; nums is 1-indexed
        if( n == 1 )
            return nums[0];

        // we need to determine the indicies which we can group with each other
        auto groups = group_indicies(n);

        long long ans = 0LL;
        for(auto ito = groups.begin(); ito != groups.end(); ++ito) {
            long long sum = 0LL;
            for(auto iti = ito->second.begin(); iti != ito->second.end(); ++iti) {
                 // cout << *iti << " ";
                sum += nums[*iti - 1];
            }
            // cout << endl;
            ans = max(ans,sum);
        }

        return ans;
    }
};
