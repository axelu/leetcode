
// 1365. How Many Numbers Are Smaller Than the Current Number
// https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/


class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        auto n = nums.size();

        int count[500]; memset(count,0,sizeof count);
        int accum[101]; memset(accum,0,sizeof accum);

        int mx = 0;
        for(int i = 0; i < n; ++i) {
            ++count[nums[i]];
            mx = max(mx,nums[i]);
        }
        int sum = 0;
        for(int i = 1; i <= mx; ++i) {
            sum += count[i-1];
            accum[i] = sum;
        }

        vector<int> r;
        for(int i = 0; i < n; ++i)
            r.push_back(accum[nums[i]]);

        return r;
    }
};
