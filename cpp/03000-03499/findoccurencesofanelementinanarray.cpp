
// 3159. Find Occurrences of an Element in an Array
// https://leetcode.com/problems/find-occurrences-of-an-element-in-an-array/




class Solution {
public:
    vector<int> occurrencesOfElement(vector<int>& nums, vector<int>& queries, int x) {

        vector<int> occurence;
        int occ = 0;
        for(int i = 0; i < nums.size(); ++i)
            if( nums[i] == x ) {
                occurence.push_back(i);
                ++occ;
            }

        int q_sz = queries.size();
        vector<int> ans(q_sz, -1);
        for(int i = 0; i < q_sz; ++i)
            if( queries[i] - 1 < occ )
                ans[i] = occurence[queries[i] - 1];

        return ans;
    }
};
