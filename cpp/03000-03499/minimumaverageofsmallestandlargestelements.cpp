
// 3194. Minimum Average of Smallest and Largest Elements
// https://leetcode.com/problems/minimum-average-of-smallest-and-largest-elements/



class Solution {
public:
    double minimumAverage(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int n = nums.size(); // n is even
        double ans = DBL_MAX;

        for(int i = 0, j = n-1; i < j ; ++i,--j) {
            double avg = (nums[i] + nums[j]) / 2.0;
            ans = min(ans, avg);
        }

        return ans;
    }
};
