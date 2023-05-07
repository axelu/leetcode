
// 2134. Minimum Swaps to Group All 1's Together II
// https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/



class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();

        // let the number of 1s in nums be ones
        // look for the sliding window of length ones with the most ones in it
        // diff to ones is the answer
        // slide the window accross the end, as our array nums is circular

        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];

        int ones = prefixSum[n];

        int mx = 0;
        for(int i = 0; i < n; ++i) {

            int cnt = prefixSum[min(i + ones, n)] - prefixSum[i];

            if( i + ones > n-1 )
                cnt += prefixSum[ones - (n-i)];

            mx = max(mx,cnt);
        }

        return ones - mx;
    }
};
