
// 90. Subsets II
// https://leetcode.com/problems/subsets-ii/
// day 3 August 2021 challenge
// https://leetcode.com/explore/featured/card/august-leetcoding-challenge-2021/613/week-1-august-1st-august-7th/3837/





class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();

        vector<vector<int>> ans;
        vector<int> t;
        set<vector<int>> st;

        sort(nums.begin(),nums.end());

        int j;
        for(int i = 0; i < pow(2,n); ++i) {
            t.clear();
            for(j = 0; j < n; ++j) {
                if( i & (1<<j) ) t.push_back(nums[j]);
            }
            auto p = st.insert(t);
            if( p.second )
                ans.push_back(t);
        }

        return ans;
    }
};
