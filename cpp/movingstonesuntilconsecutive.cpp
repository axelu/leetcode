
// 1033. Moving Stones until Consecutive
// https://leetcode.com/problems/moving-stones-until-consecutive/


class Solution {
public:
    vector<int> numMovesStones(int a, int b, int c) {
        int s1,s2,s3;
        s1 = min({a,b,c});
        s3 = max({a,b,c});
        if( a != s1 && a != s3) s2 = a;
        if( b != s1 && b != s3) s2 = b;
        if( c != s1 && c != s3) s2 = c;

        // cout << s1 << " " << s2 << " " << s3 << endl;

        if( s2 - s1 == 1 && s3 - s2 == 1 ) return {0,0};
        int mn = s2 - s1 <= 2 || s3 - s2 <= 2 ? 1 : 2;
        int mx = s3-s2-1 + s2-s1-1;

        return {mn,mx};
    }
};
