
// 593. Valid Square
// https://leetcode.com/problems/valid-square/
// day 11 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/565/week-2-november-8th-november-14th/3527/


class Solution {
private:
    long dis(array<long,2>& p1, array<long,2>& p2) {
        // ommitting square rooting
        return (p2[1] - p1[1]) * (p2[1] - p1[1]) + (p2[0] - p1[0]) * (p2[0] - p1[0]);
    }
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        vector<array<long,2>> vp = {
            {(long)p1[0],(long)p1[1]},
            {(long)p2[0],(long)p2[1]},
            {(long)p3[0],(long)p3[1]},
            {(long)p4[0],(long)p4[1]}};
        sort(begin(vp),end(vp));

        // checking four sides for equality and not 0
        long p0p1 = dis(vp[0],vp[1]);
        long p1p3 = dis(vp[1],vp[3]);
        long p3p2 = dis(vp[3],vp[2]);
        long p2p0 = dis(vp[2],vp[0]);
        if( p0p1 == 0 || p0p1 != p1p3 || p1p3 != p3p2 || p3p2 != p2p0 ) return false;

        // checking diagonals
        long p0p3 = dis(vp[0],vp[3]);
        long p1p2 = dis(vp[1],vp[2]);
        return p0p3 == p1p2;
    }
};
