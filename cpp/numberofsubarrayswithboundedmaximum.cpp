
// 795. Number of Subarrays with Bounded Maximum
// https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/
// day 17 June 2021 challenge
// https://leetcode.com/explore/featured/card/june-leetcoding-challenge-2021/605/week-3-june-15th-june-21st/3782/





class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        int N = nums.size();
        // example 1 left = 2, right = 3
        // idx 0 1 2 3
        //     2 1 4 3
        //     - - x - greater than right
        //     - x - - smaller than left
        // - a possible subarray can never include an element greater than right, that is a demarcation line
        // - if a subarray includes an element smaller than left, than it must include at
        //   least one element between left and right
        // formula for number of contiguous subarrays: subarrayCnt = n * (n+1)/2
        // if we count the number of elements less than less, we can subtract the number of
        // subarrays that could be formed using those elements from the number of all possible
        // subarrays to get to that answer.

        int ans = 0;

        int l = 0, r = 0, n;
        int smallerThanLeft = 0;
        for(; r < N; ++r) {
            if( nums[r] > right ) {
                // the current element cannot be included in a subarray
                // lets tally up the possible subarrays to this point
                // and then skip this element
                n = r-l;
                ans += (n*(n+1)/2) - (smallerThanLeft*(smallerThanLeft+1)/2);

                // reset
                smallerThanLeft = 0;
                l = r+1;
            } else if( nums[r] < left ) {
                ++smallerThanLeft;
            } else {
                // left <= nums[r] <= right
                // subtract the number of subarrays formed
                // of only smaller elements
                ans -= smallerThanLeft*(smallerThanLeft+1)/2;
                smallerThanLeft = 0;
            }

        }
        // finish up
        n = r-l;
        ans += (n*(n+1)/2) - (smallerThanLeft*(smallerThanLeft+1)/2);


        return ans;
    }
};
