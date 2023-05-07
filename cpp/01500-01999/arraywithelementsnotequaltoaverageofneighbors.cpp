
// 1968. Array With Elements Not Equal to Average of Neighbors
// https://leetcode.com/problems/array-with-elements-not-equal-to-average-of-neighbors/




class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();

        // the idea is to put numbers smaller than the median on odd indices
        // and the remaining numbers on even indices

        priority_queue<int,vector<int>,greater<int>> pq;
        for(int x: nums)
            pq.push(x);

        for(int i = 1; i < n; i += 2) {
            nums[i] = pq.top();
            pq.pop();
        }
        for(int i = 0; i < n; i += 2) {
            nums[i] = pq.top();
            pq.pop();
        }

        return nums;
    }
};
