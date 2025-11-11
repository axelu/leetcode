
// 3718. Smallest Missing Multiple of K
// https://leetcode.com/problems/smallest-missing-multiple-of-k/




class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        set<int> mk;
        for(int x: nums)
            if( x % k == 0 )
                mk.insert(x);

        if( mk.empty() )
            return k;

        int f = 1;
        for(int x: mk) {
            if( x != f * k )
                return f * k;
            ++f;
        }

        return f * k;
    }
};
