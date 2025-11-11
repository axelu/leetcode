
// 3698. Split Array With Minimum Difference
// https://leetcode.com/problems/split-array-with-minimum-difference/



class Solution {
private:
    bool is_strictly_decreasing(vector<int>& nums, int s) {
        // 0 < s < n
        // returns true if nums is strictly decreasing starting from index s

        int n = nums.size();

        for(int i = s+1; i < n; ++i)
            if( nums[i-1] <= nums[i] )
                return false;

        return true;
    }

    bool is_strictly_increasing(vector<int>& nums, int e) {

        // returns true if nums is strictly increasing up to index e
        for(int i = 1; i <= e; ++i)
            if( nums[i-1] >= nums[i] )
                return false;
        return true;
    }

public:
    long long splitArray(vector<int>& nums) {
        int n = nums.size(); // 2 <= n <= 1e5

        if( n == 2 )
            return abs(nums[0] - nums[1]);

        // a valid array has either 1 or 2 peak elements
        // 1 peak
        //              x
        //           x     x
        //        x           x
        // splits ----|--------
        //        -------|-----
        //
        // 2 peaks
        //              x  x
        //           x        x
        //        x              x
        // split  -------|--------
        //
        // edge case peak at end
        //              x
        //           x
        //        x
        // split  ----|--
        // edge case peak at begin
        //        x
        //           x
        //              x
        // split  --|----

        long long prefixSum[100001];
        prefixSum[0] = 0LL;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + (long long)nums[i-1];

        if( nums[0] >= nums[1] ) {
            if( !is_strictly_decreasing(nums, 1) )
                return -1LL;
            long long left = prefixSum[1];
            long long right = prefixSum[n] - prefixSum[1];
            return abs(left - right);
        }

        if( nums[n-2] <= nums[n-1] ) {
            if( !is_strictly_increasing(nums, n-2) )
                return -1LL;
            long long left = prefixSum[n-1];
            long long right = prefixSum[n] - prefixSum[n-1];
            return abs(left - right);
        }

        for(int i = 1; i < n; ++i) {
            if( nums[i-1] < nums[i] )
                continue;

            // either nums[i-1] == nums[i] or nums[i-1] > nums[i]
            if( !is_strictly_decreasing(nums, i) )
                return -1LL;

            if( nums[i-1] == nums[i] ) {
                long long left = prefixSum[i];
                long long right = prefixSum[n] - prefixSum[i];
                return abs(left - right);
            }

            // A
            long long leftA = prefixSum[i-1];
            long long rightA = prefixSum[n] - prefixSum[i-1];
            long long A = abs(leftA - rightA);

            // B
            long long leftB = prefixSum[i];
            long long rightB = prefixSum[n] - prefixSum[i];
            long long B = abs(leftB - rightB);

            return min(A, B);
        }

        return -1LL; // should never get here
    }
};
