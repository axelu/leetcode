
// 137. Single Number II
// https://leetcode.com/problems/single-number-ii/


class Solution {
public:
    int singleNumber(vector<int>& nums) {
        size_t n = nums.size();
        if( 0 == n ) return 0;
        if( 1 == n ) return nums[0];
        // assume otherwise n >= 4

        unordered_map<int,int> um;
        um.reserve(n/3 + 1);
        pair<unordered_map<int,int>::iterator,bool> p;
        for(int i = 0; i < n; ++i) {
            p = um.insert({nums[i],1});
            if( !p.second ) {
                if( p.first->second == 2 )
                    um.erase(nums[i]);
                else
                    ++p.first->second;
            }
        }

        return um.begin()->first;
    }
};
