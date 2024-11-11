
// 3284. Sum of Consecutive Subarrays
// https://leetcode.com/problems/sum-of-consecutive-subarrays/





class Solution {
private:

    const long mod = 1000000007;

    // https://www.geeksforgeeks.org/sum-of-all-subarrays/
    // function compute sum all sub-array
    long SubArraySum(vector<int>& nums, int s, int e) {
        if( s == e )
            return nums[s];

        int n = e - s + 1;

        long result = 0L;

        // computing sum of subarray using formula
        for(int i = s; i <= e; ++i)
            result = (result + ((long long)nums[i] * ((i-s) + 1) * (n - (i-s)))) % mod;

        return result;
    }

public:
    int getSum(vector<int>& nums) {
        int n = nums.size();

        long ans = 0L;

        int dir = 0; // direction 0 undefined, or 1 or -1
        int i = 0;
        for(int j = 0; j < n; ++j) {

            // look ahead
            if( j + 1 < n ) {

                int diff = nums[j] - nums[j+1];
                if( diff == -1 || diff == 1 ) {

                    if( j - i == 0 ) {
                        // we are establishing a direction
                        dir = diff;

                    } else if( diff == dir ) {
                        // keep going

                    } else {
                        // we are changing directions
                        dir = diff;

                        // tally
                        ans = (ans + SubArraySum(nums, i, j)) % mod;
                        // we must not doublecount our pivot element
                        ans = ans - nums[j];
                        if( ans < 0L )
                            ans += mod;
                        i = j; // we can start from current position
                    }

                } else {
                    // tally
                    ans = (ans + SubArraySum(nums, i, j)) % mod;
                    i = j+1;
                    // j will advance via loop
                    dir = 0;
                }

            } else {
                // tally
                ans = (ans + SubArraySum(nums, i, j)) % mod;
                // j will advance via loop
            }
        }

        return ans;
    }
};
