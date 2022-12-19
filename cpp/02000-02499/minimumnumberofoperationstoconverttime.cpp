
// 2224. Minimum Number of Operations to Convert Time
// https://leetcode.com/problems/minimum-number-of-operations-to-convert-time/




class Solution {
private:
    int twentyfourhourtime2minutes(string t) {
        int hrs = stoi(t.substr(0,2));
        int mns = stoi(t.substr(3));

        return hrs*60 + mns;
    }

public:
    int convertTime(string current, string correct) {
        // current and correct are in the format "HH:MM"
        // current <= correct

        int current_mns = twentyfourhourtime2minutes(current);
        int correct_mns = twentyfourhourtime2minutes(correct);

        int cnt = 0;
        int d = correct_mns - current_mns;
        while( d != 0 ) {
            if( d >= 60 )
                d -= 60;
            else if( d >= 15 )
                d -= 15;
            else if( d >= 5 )
                d -= 5;
            else if( d >= 1 )
                d -= 1;
            ++cnt;
        }

        return cnt;
    }
};
