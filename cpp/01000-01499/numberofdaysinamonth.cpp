
// 1118. Number of Days in a Month
// https://leetcode.com/problems/number-of-days-in-a-month/





class Solution {
private:
    bool isLeapYear(const int& year) {
        bool isLeap;
        if( year % 4 != 0) {isLeap = false;}
        else if( year % 25 != 0 ) {isLeap = true;}
        else if( year % 16 != 0 ) {isLeap = false;}
        else {isLeap = true;}
        return isLeap;
    }

public:
    int numberOfDays(int Y, int M) {

        int ans;
        switch(M) {
            case 1 :  ans = 31;
                      break;
            case 2 :  ans = isLeapYear(Y) ? 29 : 28;
                      break;
            case 3 :  ans = 31;
                      break;
            case 5 :  ans = 31;
                      break;
            case 7 :  ans = 31;
                      break;
            case 8 :  ans = 31;
                      break;
            case 10 : ans = 31;
                      break;
            case 12 : ans = 31;
                      break;
            default : ans = 30;
                      break;
        }
        return ans;
    }
};
