
// 2333. Minimum Sum of Squared Difference
// https://leetcode.com/problems/minimum-sum-of-squared-difference/




class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        // as we can use k1 and k2 to +1 and -1 the value in the respective array,
        // we can treat them as one, because if we run out of k1 lets say,
        // we can use k2 to decrease the difference on nums2, so it doesn't matter
        int n = nums1.size(); // nums1.size() == nums2.size()
        int k = k1 + k2;

        long long cnt[100001];memset(cnt,0,sizeof cnt);
        int mx = -1;
        for(int i = 0; i < n; ++i) {
            int t = abs(nums1[i] - nums2[i]);
            ++cnt[t];
            mx = max(mx,t);
        }

        long long i = mx;
        for(; i > 0; --i) {
            if( k >= cnt[i] ) {
                cnt[i-1] += cnt[i];
                k -= cnt[i];
            } else {
                cnt[i-1] += k;
                cnt[i] -= k;
                // k will become 0, we need to start our sum from here
                break;
            }
        }

        long long ans = 0;

        for(; i > 0; --i)
            if( cnt[i] > 0 )
                ans += (i*i) * cnt[i];

        return ans;
    }
};
