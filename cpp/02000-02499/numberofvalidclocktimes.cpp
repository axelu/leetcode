
// 2437. Number of Valid Clock Times
// https://leetcode.com/problems/number-of-valid-clock-times/



/*
"nn:nn"
"?n:nn"
"n?:nn"
"nn:?n"
"nn:n?"
"??:nn"
"?n:?n"
"?n:n?"
"n?:?n"
"n?:n?"
"nn:??"
"??:?n"
"??:n?"
"?n:??"
"n?:??"
"??:??"
*/
class Solution {
public:
    int countTime(string time) {
        // hh:mm
        int f2 = 1;
        if( time[3] == '?' && time[4] == '?' )
            f2 = 60;
        else if( time[3] != '?' && time[4] == '?' )
            f2 = 10;
        else if( time[3] == '?' && time[4] != '?')
            f2 = 6;

        int f1 = 24;
        if( time[1] == '?' ) {
            // peek backward
            if( time[0] == '?' )
                f1 = 24;
            else if( time[0] == '0' || time[0] == '1' )
                f1 = 10;
            else  // time[0] == '2'
                f1 = 4;
        }  else {
            if( time[0] != '?' )
                f1 = 1;
            else if( time[1] > '3' )
                f1 = 2;
            else
                f1 = 3;
        }

        return f1*f2;
    }
};
