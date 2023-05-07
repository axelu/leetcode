
// 681. Next Closest Time
// https://leetcode.com/problems/next-closest-time/



class Solution {
private:
    void increaseByOne(int tt[]) {
        ++tt[3];
        if( tt[3] == 10 ) {
            tt[3] = 0;
            ++tt[2];
            if( tt[2] == 6 ) {
                tt[2] = 0;
                ++tt[1];
                if( tt[1] == 4 && tt[0] == 2 ) {
                    tt[0] = 0;
                    tt[1] = 0;
                }
                if( tt[1] == 10 ) {
                    tt[1] = 0;
                    ++tt[0];
                }
            }
        }
    }

public:
    string nextClosestTime(string time) {

        int tt[4];
        vector<bool> have(10,false);

        tt[0] = time[0] - '0'; have[tt[0]] = true;
        tt[1] = time[1] - '0'; have[tt[1]] = true;
        tt[2] = time[3] - '0'; have[tt[2]] = true;
        tt[3] = time[4] - '0'; have[tt[3]] = true;

        for(int i = 1; i <= 3600; ++i) {
            increaseByOne(tt);
            if( have[tt[0]] && have[tt[1]] && have[tt[2]] && have[tt[3]] ) {
                time[0] = tt[0] + '0';
                time[1] = tt[1] + '0';
                time[3] = tt[2] + '0';
                time[4] = tt[3] + '0';
                break;
            }
        }

        return time;
    }
};
