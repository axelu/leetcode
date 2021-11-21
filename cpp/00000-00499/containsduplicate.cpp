
// 217. Contains Duplicate
// https://leetcode.com/problems/contains-duplicate/


class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        if( nums.empty() || nums.size() == 1) return false;

        unordered_set<int> s;
        for(int i : nums)
            if( !s.insert(i).second ) return true;

        return false;
    }
};
