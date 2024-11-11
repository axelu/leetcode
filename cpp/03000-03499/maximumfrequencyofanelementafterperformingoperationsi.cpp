
// 3346. Maximum Frequency of an Element After Performing Operations I
// https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/





class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int n = nums.size();

        int cnt[100001];memset(cnt,0,sizeof cnt);
        int cnt_mx = 0;
        for(int i = 0; i < n; ++i)
            cnt_mx = max(cnt_mx, ++cnt[nums[i]]);

        if( k == 0 || numOperations == 0 ) {
            // the answer is the most frequent val in nums
            return cnt_mx;
        }

        if( cnt_mx == n )
            return n;

        int prefixSum[100002];
        prefixSum[0] = 0;
        for(int i = 1; i <= 100001; ++i)
            prefixSum[i] = prefixSum[i-1] + cnt[i-1];

        int ans = 0;

        for(int i = 1; i <= 100000; ++i) {

            // a how many in range [i-k,i-1]
            // b how many of me aka i
            // c how many in range [i+1,i+k]

            int a = 0;
            int b = cnt[i];
            int c = 0;

            if( i == 1 ) {
                // only look in range [i+1,i+k] respectively 2..100000
                c = prefixSum[min(100001,i+k+1)] - prefixSum[2];

            } else if( i == 100000 ) {
                // only look in range [i-k,i-1]
                a = prefixSum[100000] - prefixSum[i-k];

            } else {
                a = prefixSum[i] - prefixSum[max(0, i-k)];
                c = prefixSum[min(100001,i+k+1)] - prefixSum[i+1];

            }

            ans = max(ans, min(numOperations, a + c) + b);
        }

        return ans;
    }
};

/* test cases
[1,4,5]
1
2
[5,11,20,20]
5
1
[88,53]
27
2
[51,17,70]
10
3
*/
