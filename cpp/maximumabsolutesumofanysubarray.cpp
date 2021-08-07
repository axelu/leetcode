
// 1749. Maximum Absolute Sum of Any Subarray
// https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/





class Solution {
private:
    // maximum subarray Kadene's algorithm
    int maxSubArraySum(int a[], int size) {

        int max_so_far = INT_MIN;
        int max_ending_here = 0;

        for(int i = 0; i < size; ++i) {

            max_ending_here = max_ending_here + a[i];

            if( max_so_far < max_ending_here )
                max_so_far = max_ending_here;

            if( max_ending_here < 0 )
                max_ending_here = 0;
        }
        return max_so_far;
    }


    // minimum subarray Kadene's algorithm
    int minSubArraySum(int a[], int size) {

        int min_so_far = INT_MAX;
        int min_ending_here = 0;

        for(int i = 0; i < size; ++i) {

            min_ending_here = min_ending_here + a[i];

            if( min_so_far > min_ending_here )
                min_so_far = min_ending_here;

            if( min_ending_here > 0 )
                min_ending_here = 0;
        }
        return min_so_far;
    }

public:
    int maxAbsoluteSum(vector<int>& nums) {

        int mx = abs(maxSubArraySum(nums.data(),nums.size()));
        int mn = abs(minSubArraySum(nums.data(),nums.size()));

        return mx > mn ? mx : mn;
    }
};
