
// 2971. Find Polygon With the Largest Perimeter
// https://leetcode.com/problems/find-polygon-with-the-largest-perimeter/





class Solution {
public:
    long long largestPerimeter(vector<int>& nums) {
        int n = nums.size(); // 3 <= n <= 1e5

        sort(nums.begin(),nums.end());

        long long sum = -1LL;
        long long running_sum = nums[0] + nums[1];
        for(int i = 2; i < n; ++i) {
            if( running_sum > (long long)nums[i] )
                sum = running_sum + (long long)nums[i];

            running_sum += (long long)nums[i];
        }

        return sum;
    }
};
