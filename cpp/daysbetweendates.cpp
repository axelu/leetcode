
// 1360. Number of Days Between Two Dates
// https://leetcode.com/problems/number-of-days-between-two-dates/



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

    int f(string& date) {
        // date string format YYYY-MM-DD
        // returns number of days from 1900-01-01 to date

        int r;

        // year
        int yr = stoi(date.substr(0,4));
        r = 365 * ( yr - 1900 );
        for(int i = 1900; i < yr; ++i) if(isLeapYear(i)) ++r;

        // month
        int mo = stoi(date.substr(5,2));
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
        r += stoi(date.substr(8,2)) - 1;

        return r;
    }
public:
    int daysBetweenDates(string date1, string date2) {
        // date string format YYYY-MM-DD

        return abs(f(date1) - f(date2));
    }
};
