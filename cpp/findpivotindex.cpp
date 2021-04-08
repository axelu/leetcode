
// 724. Find Pivot Index
// https://leetcode.com/problems/find-pivot-index/



class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int n = nums.size(); // 1 <= nums.length <= 104
        if( n == 1 ) return 0;

        int sum[n]; memset(sum,0,sizeof sum);
        sum[0] = nums[0];
        for(int i = 1; i < n; ++i)
            sum[i] = sum[i-1]+nums[i];

        int total = sum[n-1];
        int lsum = 0;
        int rsum;
        for(int i = 0; i < n; ++i) {
            rsum = total-lsum-nums[i];
            // cout << " i " << i << " lsum " << lsum << " rsum " << rsum << endl;
            if( rsum == lsum ) return i;
            lsum = sum[i];
        }
        return -1;
    }
};
