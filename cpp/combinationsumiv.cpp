
// Combination Sum IV
// https://leetcode.com/problems/combination-sum-iv/

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {

        vector<unsigned long> top(target + 1, 0);
        sort(nums.begin(), nums.end());
        top[0] = 1;
        for(int i = 1; i <= target; ++i) {

            int n = 0; // number possibilities to reach top
            for(auto it = nums.begin(); it != nums.end(); ++it) {

                int rem = i - *it;
                if (rem < 0) break;

                n += top[rem];
            }
            top[i] = n;
        }

        return top[target];
    }
};
