
// 2537. Count the Number of Good Subarrays
// https://leetcode.com/problems/count-the-number-of-good-subarrays/




class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        int n = nums.size();
        // number pairs: n * (n-1) / 2

        long long ans = 0;


        // sliding window

        unordered_map<int,long long> um;// int, number of occurences
        long long number_pairs = 0;
        int i = 0;                      // left index
        for(int j = 0; j < n; ++j) {    // right index

            // count the number of the same digits in the current window
            // calculate the number of pairs we can make and keep track of total
            // if total >= k, then any array starting at i and ending at [j,n-1] is a good subarray
            // we can then reduce the window size
            // but even when reducing the window size, check if we still can make k pairs

            // current number of pairs we were able to make with nums[j]
            long long curj = um[nums[j]] * (um[nums[j]] - 1LL) / 2LL;

            ++um[nums[j]];

            // new number of pairs we are able to make with nums[j]
            long long newj = um[nums[j]] * (um[nums[j]] - 1LL) / 2LL;

            number_pairs += ( newj - curj );

            while( number_pairs >= k ) {
                ans += n - j;

                // current number of pairs we were able to make with nums[i]
                long long curi = um[nums[i]] * (um[nums[i]] - 1LL) / 2LL;

                --um[nums[i]];

                // new number of pairs we are able to make with nums[i]
                long long newi = um[nums[i]] * (um[nums[i]] - 1LL) / 2LL;

                number_pairs -= ( curi - newi );

                ++i;
            }
        }

        return ans;
    }
};
