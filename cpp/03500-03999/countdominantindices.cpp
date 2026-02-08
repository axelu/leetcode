
// 3833. Count Dominant Indices
// https://leetcode.com/problems/count-dominant-indices/



class Solution {
public:
    int dominantIndices(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 0;

        int ans = 0;
        int sum = nums[n-1];
        for(int i = n-2, cnt = 1; i >= 0; --i, ++cnt) {
            int avg = sum/cnt;
            int num = nums[i];
            if( num > avg )
                ++ans;
            sum += num;
        }

        return ans;
    }
};
