
// 2465. Number of Distinct Averages
// https://leetcode.com/problems/number-of-distinct-averages/




class Solution {
public:
    int distinctAverages(vector<int>& nums) {
        int sums[10001];memset(sums,0,sizeof sums);

        sort(begin(nums),end(nums));
        int cnt = 0;
        for(int i = 0, j = nums.size()-1; i < j; ++i,--j)
            if( sums[nums[i]+nums[j]] == 0 ) {
                sums[nums[i]+nums[j]] = 1;
                ++cnt;
            }

        return cnt;
    }
};
