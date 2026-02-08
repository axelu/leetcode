
// 3826. Minimum Partition Score
// https://leetcode.com/problems/minimum-partition-score/

class Solution {
public:
    long long minPartitionScore(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= n <= 1000; 1 <= nums[i] <= 1e4
        // sumArr = nums[i] + nums[i+1] ... for 0 <= i < n
        // value  = sumArr * (sumArr + 1) / 2
        // worst case sumArr => 1000 * 10000 = 10000000 = 1e7
        // worst case value  => 1e7 * (1e7 + 1)/2 = 50000005000000
        //                           LLONG_MAX 9223372036854775807

        if( k == 1 ) {
            long long sum = accumulate(nums.begin(), nums.end(), 0LL);
            long long val = sum * (sum+1)/2;
            return val;
        }

        if( k == n ) {
            return accumulate(nums.begin(), nums.end(), 0L, [](long a, long b){
                return a + b * (b+1)/2;
            });
        }

        // brute force
        // buttom up
        vector<long long> pre(n, LLONG_MAX);
        long long arrSum = 0;
        // base case 1 bin
        for(int i = n-1; i >= k-1; --i) {
            // cout << "bins 1 i " << i << endl;
            arrSum += nums[i];
            pre[i] = arrSum * (arrSum+1)/2;
        }
        // 2..k bins
        vector<long long> cur(n, LLONG_MAX);
        for(int bins = 2; bins <= k; ++bins) {
            int i_mx = n-bins;
            int i_mn = k-bins;
            for(int i = i_mx; i >= i_mn; --i) {
                // cout << "bins " << bins << " i " << i << endl;
                arrSum = 0;
                for(int j = i; j <= i_mx; ++j) {
                    arrSum += nums[j];
                    cur[i] = min(cur[i], arrSum * (arrSum+1)/2 + pre[j+1]);
                }
            }
            cur.swap(pre);
        }

        return pre[0];
    }
};



