
// 3077. Maximum Strength of K Disjoint Subarrays
// https://leetcode.com/problems/maximum-strength-of-k-disjoint-subarrays/


class Solution {
private:
    long long rec(vector<int>& nums, int n, int i, int k, bool pre, vector<vector<vector<long long>>>& mem) {
        // cout << "rec i " << i << " k " << k << " pre " << pre << endl;
        // pre indicates if prior element was selected
        if( k == 0 )
            return 0LL;
        
        if( i == n ) {
            if( pre && k == 1 )
                return 0LL;
            else
                return -1000000000000001LL;
        }
        
        if( mem[i][k][pre] != LLONG_MIN ) {
            return mem[i][k][pre];
        }
        
        // we have a choice
        // if the prior element was selected
        //     we select the current element and continue the prior subarray OR
        //     we skip the current element and with that start a new subarray next one down OR
        //     we select the current element and start a new subarray at the current element
        // if the prior element was NOT selected
        //     we skip the current element and with that start a new subarray next one down OR
        //     we select the current element 
        
        long long ret = -1000000000000001LL;
        long long f = k % 2 ? 1LL : -1LL;
        

        if( pre ) {
            ret = max(ret, (f * (long long)nums[i] * (long long)k) + rec(nums, n, i+1, k, true, mem));
            ret = max(ret, rec(nums, n, i+1, k-1, false, mem));
            ret = max(ret, (-f * (long long)nums[i] * (long long)(k-1)) + rec(nums, n, i+1, k-1, true, mem));

        } else {
            ret = max(ret, rec(nums, n, i+1, k, false, mem));
            ret = max(ret, (f * (long long)nums[i] * (long long)k) + rec(nums, n, i+1, k, true, mem));
        }

        // cout << "rec i " << i << " k " << k << " pre " << pre << " ret " << ret << endl;
        return mem[i][k][pre] = ret;
    }
    
    
    
public:
    long long maximumStrength(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= n <= 1e4
        // cout << n << endl;
        // 1 <= k <= n;  1 <= n * k <= 1e6; k is odd
        
        // the strength of x subarrays is defined as:
        //     strength = sum[1] * x - sum[2] * (x - 1) + sum[3] * (x - 2) - sum[4] * (x - 3) + ... + sum[x] * 1 
        //     where sum[i] is the sum of the elements in the ith subarray
        // formally
        //     strength is sum of (-1)^i+1 * sum[i] * (x - i + 1) over all i's such that 1 <= i <= x
        // example x = 5
        //     strength = sum[1] * 5 - sum[2] * (5 - 1) + sum[3] * (5 - 2) - sum[4] * (5 - 3) + sum[5] * (5 - 4)
        //     strength = sum[1] * 5 - sum[2] *    4    + sum[3] *    3    - sum[4] *    2    + sum[5] *    1
        
        // we need to the find k/2 + 1 largest subarrays and the k/2 smallest subarrays
        // the relative order of the subarrays cannot be changed!!!
        
        vector<vector<vector<long long>>> mem(n,vector<vector<long long>>(k+1,vector<long long>(2,LLONG_MIN)));
        return rec(nums, n, 0, k, false, mem);
    }
};



