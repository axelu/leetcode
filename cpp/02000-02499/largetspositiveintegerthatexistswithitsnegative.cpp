
// 2441. Largest Positive Integer That Exists With Its Negative
// https://leetcode.com/problems/largest-positive-integer-that-exists-with-its-negative/



class Solution {
public:
    int findMaxK(vector<int>& nums) {
        set<int> pos;
        unordered_set<int> neg;
        for(int x: nums)
            if( x > 0 )
                pos.insert(x);
            else
                neg.insert(x);

        for(auto it = pos.rbegin(); it != pos.rend(); ++it)
            if( neg.count(-*it) )
                return *it;

        return -1;
    }
};
