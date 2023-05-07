
// 2295. Replace Elements in an Array
// https://leetcode.com/problems/replace-elements-in-an-array/




class Solution {
public:
    vector<int> arrayChange(vector<int>& nums, vector<vector<int>>& operations) {
        int n = nums.size();
        unordered_map<int,int> um; // val,idx
        for(int i = 0; i < n; ++i)
            um[nums[i]] = i;

        for(auto& v: operations) {
            auto f = um.find(v[0]);
            if( f != um.end() ) {
                nums[f->second] = v[1];
                um[v[1]] = f->second;
                um.erase(f);
            }
        }

        return nums;
    }
};
