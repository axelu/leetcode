
// 65. Valid Number
// https://leetcode.com/problems/valid-number/
// day 15 May 2021 challenge
// https://leetcode.com/explore/featured/card/may-leetcoding-challenge-2021/600/week-3-may-15th-may-21st/3744/



class Solution {
private:
    bool isInteger(string& str, int s, int e) {
        if( str[s] != '+' && str[s] != '-' && !isdigit(str[s]) )
            return false;

        if( s == e )
            return isdigit(str[s]);

        for(int i = s+1; i <= e; ++i)
            if( !isdigit(str[i]) )
                return false;

        return true;
    }

    bool isDecimal(string& str, int e, int period) {
        if( e == 0 ) return false;
        if( str[0] != '+' && str[0] != '-' && str[0] != '.' && !isdigit(str[0]) )
            return false;

        if( period == 0 ) {
            // right side has to be an integer
            // it was already checked that is only has digits
            return isInteger(str,period+1,e);
        } else if( period == e ) {
            if( period == 1 )
                return isdigit(str[0]);

            // left side has to be an integer
            return isInteger(str,0,e-1);
        } else {
            if( period == 1 )
                return isInteger(str,period+1,e);;

            // left side has to be an integer
            if( !isInteger(str,0,period-1) )
                return false;
            // right side has to be an integer
            // it was already checked that is only has digits
            return isInteger(str,period+1,e);
        }
    }
public:
    bool isNumber(string& s) {
        int n = s.size();
        if( n == 1 )
            return isdigit(s[0]);
        if( s[0] != '+' && s[0] != '-' && s[0] != '.' && !isdigit(s[0]) )
            return false;

        int period = s[0] == '.' ? 0 : -1;
        for(int i = 1; i < n; ++i) {
            if( s[i] == '.' ) {
                if( period != -1 ) return false; // more than one period
                period = i;
            } else if( s[i] == 'e' || s[i] == 'E' ) {
                if( i == 0 || i == n-1 )
                    return false;
                // right side has to be an integer
                if( !isInteger(s,i+1,n-1) )
                   return false;
                // left side can be a decimal OR an integer
                if( period != -1 ) {
                    // decimal
                    return isDecimal(s,i-1,period);
                } else {
                    // integer
                    return isInteger(s,0,i-1);
                }
            } else {
                if( !isdigit(s[i]) )
                    return false;
            }
        }
        if( period != -1 ) {
            // decimal
            return isDecimal(s,n-1,period);
        } else {
            // integer
            return isInteger(s,0,n-1);
        }
    }
};
