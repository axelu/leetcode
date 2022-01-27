
// 1052. Grumpy Bookstore Owner
// https://leetcode.com/problems/grumpy-bookstore-owner/


class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int n = customers.size(); // n == customers.length == grumpy.length

        // prefix sum when not grumpy
        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = grumpy[i-1] ? prefixSum[i-1] : customers[i-1] + prefixSum[i-1];

        int ans = 0;
        int i = 0;
        int windowSum = 0, lsum,rsum;
        for(int j = 0; j < n; ++j) {
            windowSum += customers[j];

            // sliding window
            if( j-i+1 < minutes )
                continue;

            // left of i
            // respectively left of window
            lsum = prefixSum[i];

            // right of i+minutes
            // respectively right window
            rsum = prefixSum[n]-prefixSum[j+1];

            ans = max(ans,lsum+windowSum+rsum);

            windowSum -= customers[i];
            ++i;
        }

        return ans;
    }
};
