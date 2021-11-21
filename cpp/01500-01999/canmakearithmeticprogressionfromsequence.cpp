
// 1502. Can Make Arithmetic Progression From Sequence
// https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/


class Solution {
public:
    bool canMakeArithmeticProgression(vector<int>& arr) {
        if( arr.size() == 2 ) return true;
        auto it = arr.begin();
        auto ae = arr.end();

        sort(it, ae);
        int d = *it - *(it+1);
        for(it = it + 1; it != ae - 1; ++it) {
            if ( *it - *(it+1) != d ) return false;
        }

        return true;
    }
};
