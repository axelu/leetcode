
// 2409. Count Days Spent Together
// https://leetcode.com/problems/count-days-spent-together/


class Solution {
private:
    int dayspermonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int dayofyear(string MMDD) {
        // MM-DD
        // 01-01 will be day 1
        int m = stoi(MMDD.substr(0,2))-1;
        int d = 0;
        for(int i = 0; i < m; ++i)
            d += dayspermonth[i];

        d += stoi(MMDD.substr(3,2));

        return d;
    }

public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        // MM-DD

        int as = dayofyear(arriveAlice);
        int ae = dayofyear(leaveAlice);
        int bs = dayofyear(arriveBob);
        int be = dayofyear(leaveBob);

        if( ae < bs || as > be ) // no overlap
            return 0;

        if( as < bs ) {
            if( ae == bs )
                return 1;
            else if( ae > bs && ae < be )
                return ae-bs+1;
            else // ( ae >= be )
                return be-bs+1;
        } else if( as == bs ) {
            if( ae < be )
                return ae-as+1;
            else
                return be-bs+1;
        } else if( as > bs && as < be ) {
            if( ae < be )
                return ae-as+1;
            else
                return be-as+1;
        } else
            return 1;

    }
};
