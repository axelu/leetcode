
// 845. Longest Mountain in Array
// https://leetcode.com/problems/longest-mountain-in-array/
// day 16 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/566/week-3-november-15th-november-21st/3533/



class Solution {
public:
    int longestMountain(vector<int>& A) {
        size_t n = A.size();
        if( n <= 2 ) return 0;

        int r = 0; // distance between a local min and a subsequent local max
        int mx = 0, s = 0;
        int md = 0; // decline, initial mode
        int ai,ap;
        for(int i = 1; i < n; ++i) {
            ai = A[i];
            ap = A[i-1];
            if( ai == ap) {
                mx = 0;
                md = 0;
            } else if( ai > ap ) {
                mx = ai;
                if( md == 0 ) s = i-1;
                md = 1;
            } else if( ai < mx ) { // ai < ap
                r = max(r,i-s);
                md = 0;
            }
        }

        return r == 0 ? 0 : r+1;
    }
};
