
// 1154. Day of the Year
// https://leetcode.com/problems/day-of-the-year/



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

    int nbrDaysOfMonth(const int& month, const int& year) {
        int r;
        switch(month) {
            case 1 :  r = 31;
                      break;
            case 2 :  r = isLeapYear(year) ? 29 : 28;
                      break;
            case 3 :  r = 31;
                      break;
            case 5 :  r = 31;
                      break;
            case 7 :  r = 31;
                      break;
            case 8 :  r = 31;
                      break;
            case 10 : r = 31;
                      break;
            case 12 : r = 31;
                      break;
            default : r = 30;
                      break;
        }
        return r;
    }

public:
    int dayOfYear(string date) {

        int r = 0;
        int yr = stoi(date.substr(0,4));
        int mo = stoi(date.substr(5,2));
        for(int i = 1; i < mo; ++i)
            r += nbrDaysOfMonth(i,yr);

        return r + stoi(date.substr(8,2));
    }
};
