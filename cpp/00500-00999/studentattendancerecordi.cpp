
// 551. Student Attendance Record I
// https://leetcode.com/problems/student-attendance-record-i/



class Solution {
public:
    bool checkRecord(string s) {
        int n = s.size();
        if( n == 1 ) return true;

        int A = 0;
        int L = 0;
        for(int i = 0; i < n; ++i) {
            if( s[i] == 'A' ) {
                ++A;
                if( A == 2 ) return false;
            }
            if( i == 0 && s[i] == 'L' ) ++L;
            if( i > 0 ) {
                if( s[i-1] == 'L' && s[i] == 'L' ) {
                    ++L;
                    if( L == 3 ) return false;
                } else if( s[i-1] != 'L' && s[i] == 'L' ) {
                    L = 1;
                }
            }
        }
        return true;
    }
};
