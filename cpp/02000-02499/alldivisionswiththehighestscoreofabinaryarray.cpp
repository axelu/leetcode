
// 2155. All Divisions With the Highest Score of a Binary Array
// https://leetcode.com/problems/all-divisions-with-the-highest-score-of-a-binary-array/



class Solution {
public:
    vector<int> maxScoreIndices(vector<int>& nums) {
        int n = nums.size();

        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];

        vector<int> ans{0};
        int mx = prefixSum[n];
        int nbr_elements_left = 1;
        for(int i = 1; i <= n; ++i) {

            int left_score  = i - prefixSum[i];
            int right_score = prefixSum[n] - prefixSum[i];

            if( left_score + right_score > mx ) {
                ans.clear();
                ans.push_back(i);
                mx = left_score + right_score;
            } else if( left_score + right_score == mx ) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};
