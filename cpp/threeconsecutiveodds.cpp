
// Three consecutive odds
// https://leetcode.com/problems/three-consecutive-odds/


class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        if( arr.size() == 0 ) return false;

        int c = 0;
        for(int i : arr) {
            c = ( i % 2 != 0 ) ? c + 1 : c = 0;
            if( c == 3 ) return true;
        }

        return false;
    }
};
