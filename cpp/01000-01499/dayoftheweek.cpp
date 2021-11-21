
// 1185. Day of the Week
// https://leetcode.com/problems/day-of-the-week/


class Solution {
// see 1360. Number of Days Between Two Dates
// https://leetcode.com/problems/number-of-days-between-two-dates/
private:
    bool isLeapYear(const int& year) {
        bool isLeap;
        if( year % 4 != 0) {isLeap = false;}
        else if( year % 25 != 0 ) {isLeap = true;}
        else if( year % 16 != 0 ) {isLeap = false;}
        else {isLeap = true;}
        return isLeap;
    }

    int f(int day, int mo, int yr) {
        // returns number of days from 1900-01-01 to date

        int r;

        // year
        r = 365 * ( yr - 1900 );
        for(int i = 1900; i < yr; ++i) if(isLeapYear(i)) ++r;

        // month
        for(int i = 1; i < mo; ++i) {
            switch(i) {
                case 1 :  r += 31;
                          break;
                case 2 :  r += isLeapYear(yr) ? 29 : 28;
                          break;
                case 3 :  r += 31;
                          break;
                case 5 :  r += 31;
                          break;
                case 7 :  r += 31;
                          break;
                case 8 :  r += 31;
                          break;
                case 10 : r += 31;
                          break;
                case 12 : r += 31;
                          break;
                default : r += 30;
                          break;
                }
        }

        // day
        r += day - 1;

        return r;
    }
public:
    string dayOfTheWeek(int day, int month, int year) {
        int d = f(day,month,year) % 7;
        string r;
        switch(d) {
            case 0: r = "Monday";
                    break;
            case 1: r = "Tuesday";
                    break;
            case 2: r = "Wednesday";
                    break;
            case 3: r = "Thursday";
                    break;
            case 4: r = "Friday";
                    break;
            case 5: r = "Saturday";
                    break;
            default: r = "Sunday";
                    break;
        }

        return r;
    }
};
