
// 2200. Find All K-Distant Indices in an Array
// https://leetcode.com/problems/find-all-k-distant-indices-in-an-array/




class Solution {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        int n = nums.size();

        vector<int> v; // indexes i in nums where nums[i] == key
        for(int i = 0; i < n; ++i)
            if( nums[i] == key )
                v.push_back(i);

        vector<int> ans;
        if( v.empty() )
            return ans;

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < v.size(); ++j) {
                if( abs(i - v[j]) <= k ) {
                    ans.push_back(i);
                    break;
                }
            }
        }

        return ans;
    }
};
