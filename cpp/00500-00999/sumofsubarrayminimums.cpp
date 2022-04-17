
// 907. Sum of Subarray Minimums
// https://leetcode.com/problems/sum-of-subarray-minimums/



class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        if( n == 1 )
            return arr[0];

        long mod = 1000000007;

        long ans = 0;

        stack<array<long,3>> stck; // monotonic stack
        long curr;
        for(int i = 0; i < n; ++i) {
            curr = arr[i];

            // figure out all subarrays ending at i
            while( !stck.empty() && curr <= stck.top()[0] )
                stck.pop();

            if( stck.empty() ) {
                long t = (i+1) * curr;
                ans = (ans + t) % mod;
                stck.push({arr[i],i,t});


            } else {
                long t = (i-stck.top()[1]) * curr;
                ans = (ans + t) % mod;
                ans = (ans + stck.top()[2]) % mod;

                stck.push({arr[i],i,stck.top()[2] + t});
            }
        }

        return ans;
    }
};
