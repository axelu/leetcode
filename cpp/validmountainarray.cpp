
// 941. Valid Mountain Array
// https://leetcode.com/problems/valid-mountain-array/
// day 10 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/570/week-2-december-8th-december-14th/3561/





class Solution {
public:
    bool validMountainArray(vector<int>& arr) {
        size_t n = arr.size();
        if( n < 3 ) return false;
        if( arr[0] >= arr[1] ) return false;
        if( arr[n-2] <= arr[n-1] ) return false;

        int mode = 0; // 0 increase 1 decrease
        int p = arr[0], c;
        for(int i = 1; i < n; ++i) {
            c = arr[i];
            if( p == c ) return false;
            if( mode == 0 && p > c ) mode = 1;
            if( mode == 1 && p < c ) return false;
            p = c;
        }
        return true;
    }
};
