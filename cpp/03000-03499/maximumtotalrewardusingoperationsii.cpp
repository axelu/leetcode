
// 3181. Maximum Total Reward Using Operations II
// https://leetcode.com/problems/maximum-total-reward-using-operations-ii/






class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        // we can eliminate dups and sort -> set
        set<int> st;
        for(int x: rewardValues)
            st.insert(x);
        vector<int> nums(st.begin(),st.end());
        int n = nums.size(); // 1 <= n <= 50000

        // 1 <= rewardValues[i] <= 50000


        // it is always optimal to include the largest element (after sorting asc is at position n-1)
        // we need to find the max sum < largest element which we can make from the remaining elements

        // let dp[x] indicate, if we can make amount x (yes or no)
        // our amount x can only be between 0 and largest element (or basically the constraint given in problem rewardValues[i] <= 50000)
        bool dp[50001];memset(dp,false,sizeof dp);
        dp[0] = true;
        int mx_sum = 0;
        for(int i = 0; i < n; ++i) {

            // our largest element must be greater then our current element + reward that we already have,
            // hence we don't need to check all possible amount, we only need to check up largest element minus current element
            // but also, the reward we already have must be smaller that our current element,
            // hence our limit is the smaller of the two
            int limit = min(nums[i], nums[n-1] - nums[i]);

            // check all amounts less then limit to see if we can make them
            for(int x = 0; x < limit; ++x) {
                // keep track of the amounts we can make, because we are after the largest one
                if( dp[x] ) {
                    dp[x + nums[i]] = true;
                    mx_sum = max(mx_sum, x + nums[i]);
                }
            }
        }

        return mx_sum + nums[n-1];
    }
};
