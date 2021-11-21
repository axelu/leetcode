
// 1460. Make Two Arrays Equal by Reversing Sub-arrays
// https://leetcode.com/problems/make-two-arrays-equal-by-reversing-sub-arrays/

class Solution {
public:
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        if( target == arr ) return true;

        int k = 0;
        for(int t : target) {
            auto f = find(arr.begin() + k, arr.end(), t);
            if( f != arr.end() ) {
                reverse(arr.begin() + k, f + 1);
                if( target == arr ) return true; // short circuit
            } else {
                return false;
            }
            ++k;
        }

        return true;
    }
};
