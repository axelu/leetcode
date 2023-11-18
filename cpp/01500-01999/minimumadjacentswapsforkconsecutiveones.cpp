
// 1703. Minimum Adjacent Swaps for K Consecutive Ones
// https://leetcode.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/





class Solution {
public:
    int minMoves(vector<int>& nums, int k) {
        // create array with all the indexes in nums where nums[i] == 1
        vector<int> arr;
        for(int i = 0; i < nums.size(); ++i)
            if( nums[i] == 1 )
                arr.push_back(i);

        // if we slide a window of length k over arr (arr being our positions of 1s)
        // we know that there are k ones in that window
        // what we need to figure out is, what is the min number of moves
        // required to cluster them all together
        // example
        //      0 1 2 3 4 5 6 7 8
        // nums 1 0 1 0 1 0 1 0 1
        // k = 5
        //        0 1 2 3 4
        // -> arr 0,2,4,6,8
        // we greedily will always attempt to cluster our 1s around the middle
        // k = 5 -> mid = 0 + ((4-0)/2) = 2
        // we can figure out the min moves as follows:
        // initially move all left and right of mid to mid
        //   cost left: 4-0 + 4-2 = 6  cost right: 8-4 + 6-2
        //   observation: this is the same as the right prefixSum[3,4] - left prefixSum[0,1]
        // because we don't move them onto the mid, we need to subtract
        // their distance from mid to their actual final position
        // final positions in our example 2,3,4,5,6
        // so 2 + 1 + 0 + 1 + 2 must be subtracted
        // in our example (k-1)/2 gives us the distance of the furthest element, let that be radius around the middle r
        // on each side it is really the sum of positive integers up to the furthest element
        // formula for sum of first n positive integers: n(n+1)/2
        // because we are doing that left and right, we don't divide by 2: r(r+1)
        //
        // if we keep track of min moves while sliding the window, we have our answer

        int arr_sz = arr.size();
        long prefixSum[arr_sz+1];
        prefixSum[0] = 0L;
        for(int i = 1; i <= arr_sz; ++i)
            prefixSum[i] = prefixSum[i-1] + arr[i-1];

        long ans = INT_MAX;
        long r = (k-1)/2;

        if( k % 2 == 1 ) {  // k odd
            // sliding window
            for(int i = 0; i <= arr_sz-k; ++i) { // left index of window
                int j = i + 2*r;                 // right index of window
                int m = i + r;                   // middle of the window

                long lft = prefixSum[m] - prefixSum[i];
                long rgt = prefixSum[j+1] - prefixSum[m+1];

                ans = min(ans, rgt - lft - r*(r+1));
            }


        } else {            // k even
            // if k is even, we need to compensate for the fact, that
            // if we cluster around the middle, the right side of our window is one longer

             // sliding window
            for(int i = 0; i <= arr_sz-k; ++i) { // left index of window
                int j = i + 2*r + 1;             // right index of window (one more compared to when k is even)
                int m = i + r;                   // middle of the window

                long lft = prefixSum[m] - prefixSum[i];
                long rgt = prefixSum[j+1] - prefixSum[m+1];

                ans = min(ans, rgt - lft - arr[m] - r*(r+1) - (r+1));
            }
        }

        return ans;
    }
};
