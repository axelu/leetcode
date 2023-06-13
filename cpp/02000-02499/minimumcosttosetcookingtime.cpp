
// 2162. Minimum Cost to Set Cooking Time
// https://leetcode.com/problems/minimum-cost-to-set-cooking-time/





/* it is never beneficial to add one or more leading zero's
 *
 */

class Solution {
private:

    string mmss_to_string(int mm, int ss) {
        string s;
        if( mm > 0 ) {
            if( ss == 0 ) {
                s = to_string(mm) + "00";
            } else if( ss < 10 ) {
                s = to_string(mm) + "0" + to_string(ss);
            } else {
                s = to_string(mm) + to_string(ss);
            }
        } else {
            s = to_string(ss);
        }

        return s;
    }

    int cost(string s, int startAt, int moveCost, int pushCost) {
        int n = s.size();

        int ret = 0;

        char curr = '0' + startAt;
        for(int i = 0; i < n; ++i) {

            if( curr != s[i] )
                ret += moveCost;

            ret += pushCost;

            curr = s[i];
        }

        return ret;
    }

public:
    int minCostSetTime(int startAt, int moveCost, int pushCost, int targetSeconds) {

        int ans = INT_MAX;

        int mm = targetSeconds / 60;
        int ss = targetSeconds % 60;

        if( mm < 100 ) {
            string s = mmss_to_string(mm,ss);
            ans = min(ans,cost(s,startAt,moveCost,pushCost));
        }

        if( mm > 0 ) {
            --mm;
            ss += 60;
            if( ss <= 99 ) {
                string s = mmss_to_string(mm,ss);
                ans = min(ans,cost(s,startAt,moveCost,pushCost));
            }
        }

        return ans;
    }
};
