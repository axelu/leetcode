
// 2281. Sum of Total Strength of Wizards
// https://leetcode.com/problems/sum-of-total-strength-of-wizards/





// according to approach outlined in problem's solution

class Solution {
private:
    long mod = 1000000007;

public:
    int totalStrength(vector<int>& strength) {
        int n = strength.size();

        // idea
        // for each element figure out all subarrays, for which the current element is the minimum
        // then get the sum of all such subarrays and multiply said sum with that element

        // Get the first index of the non-larger value to strength[i]'s right.
        stack<int> stck;
        vector<int> rightIndex(n,n);
        for(int i = 0; i < n; ++i) {
            while( !stck.empty() && strength[stck.top()] >= strength[i] ) {
                rightIndex[stck.top()] = i;
                stck.pop();
            }
            stck.push(i);
        }
        // clear the stck for reuse
        while( !stck.empty() )
            stck.pop();

        // Get the first index of the smaller value to strength[i]'s left.
        vector<int> leftIndex(n,-1);
        for(int i = n - 1; i >= 0; --i) {
            while( !stck.empty() && strength[stck.top()] > strength[i] ) {
                leftIndex[stck.top()] = i;
                stck.pop();
            }
            stck.push(i);
        }

        // Get the prefix sum of the prefix sum array of strength.
        long prefixSum[n+1];
        prefixSum[0] = 0L;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = (prefixSum[i-1] + strength[i-1]) % mod;
        long prefixSum_prefixSum[n+2];
        prefixSum_prefixSum[0] = 0L;
        prefixSum_prefixSum[1] = 0L;
        for(int i = 2; i <= n+1; ++i)
            prefixSum_prefixSum[i] = (prefixSum_prefixSum[i-1] + prefixSum[i-1]) % mod;

        long ans = 0L;

        // For each element in strength, we get the value of R_term - L_term.
        for(int i = 0; i < n; ++i) {
            // Get the left index and the right index.
            int leftBound = leftIndex[i];
            int rightBound = rightIndex[i];

            // Get the leftCount and rightCount (marked as L and R in the previous slides)
            int leftCount = i - leftBound;
            int rightCount = rightBound - i;

            // Get posPresum and negPresum.
            long negPresum = (prefixSum_prefixSum[i + 1] - prefixSum_prefixSum[i - leftCount + 1]) % mod;
            long posPresum = (prefixSum_prefixSum[i + rightCount + 1] - prefixSum_prefixSum[i + 1]) % mod;

            // The total strength of all subarrays that have strength[i] as the minimum.
            ans = (ans + (posPresum * leftCount - negPresum * rightCount) % mod * strength[i] % mod) % mod;
        }

        return (ans + mod) % mod; // we could be negativ, hence + mod
    }
};
