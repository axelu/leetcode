
// 1748. Sum of Unique Elements
// https://leetcode.com/problems/sum-of-unique-elements/


class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 ) return nums[0];

        unordered_map<int,int> seen;
        pair<unordered_map<int,int>::iterator,bool> p;
        int s = 0;
        for(int i = 0; i < n; ++i) {
            p = seen.insert({nums[i],1});
            if( p.second ) {
                s += nums[i];
            } else {
                if( p.first->second == 1 ) s -= nums[i];
                ++p.first->second;
            }
        }

        return s;
    }
};
