
// 2974. Minimum Number Game
// https://leetcode.com/problems/minimum-number-game/



class Solution {
public:
    vector<int> numberGame(vector<int>& nums) {
        int n = nums.size(); // n % 2 == 0

        sort(nums.begin(),nums.end());

        vector<int> ans(n);
        int j = 0;

        for(int i = 1; i < n; i += 2) {
            ans[j] = nums[i];
            ++j;
            ans[j] = nums[i-1];
            ++j;
        }

        return ans;
    }
};
