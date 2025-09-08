
// 3659. Partition Array Into K-Distinct Groups
// https://leetcode.com/problems/partition-array-into-k-distinct-groups/



class Solution {
public:
    bool partitionArray(vector<int>& nums, int k) {
        if( k == 1 )
            return true;

        int n = nums.size();
        if( n % k != 0 )
            return false;

        int group_cnt = n / k;

        int mx_cnt = 0;
        int cnt[100001]; memset(cnt,0,sizeof cnt); // 1 <= nums[i] <= 1e5
        for(int i: nums) {
            ++cnt[i];
            mx_cnt = max(mx_cnt, cnt[i]);
            if( mx_cnt > group_cnt )
                return false;
        }

        return true;
    }
};
