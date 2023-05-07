
// 1144. Decrease Elements To Make Array Zigzag
// https://leetcode.com/problems/decrease-elements-to-make-array-zigzag/




class Solution {
public:
    int movesToMakeZigzag(vector<int>& nums) {
        int n = nums.size();

        // even case: each even indexed element is greater than is adjacent elements
        int te = 0;
        for(int i = 1; i < n; i = i + 2) {
            // i is odd
            // the element at index i must be less then its adjacent elements
            // nums[i-1] > nums[i] < nums[i+1]
            int t1 = nums[i] >= nums[i-1] ? nums[i] - nums[i-1] + 1 : 0;
            int t2 = i + 1 < n && nums[i] >= nums[i+1] ? nums[i] - nums[i+1] + 1 : 0;
            te += max(t1,t2);
        }

        // odd case: each odd indexed element is greater than is adjacent elements
        int to = 0;
        for(int i = 0; i < n; i = i + 2) {
            // i is even
            // the element at index i must be less then its adjacent elements
            // nums[i-1] > nums[i] < nums[i+1]
            int t1 = i - 1 >= 0 && nums[i] >= nums[i-1] ? nums[i] - nums[i-1] + 1 : 0;
            int t2 = i + 1 < n && nums[i] >= nums[i+1] ? nums[i] - nums[i+1] + 1 : 0;
            to += max(t1,t2);
        }

        return min(te,to);
    }
};
