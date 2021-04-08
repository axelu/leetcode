
// 1688. Count of Matches in Tournament
// https://leetcode.com/problems/count-of-matches-in-tournament/


class Solution {
public:
    int numberOfMatches(int n) {


        int round = 1, matches;
        int cnt = 0;
        while(n>1) {
            if( n % 2 == 0 ) {
                matches = n / 2;
                n /= 2;
            } else {
                matches = (n - 1) / 2;
                n = (n - 1) / 2 + 1;
            }
            /*
            cout << "round " << round;
            cout << " teams " << n;
            cout << " matches " << matches;
            cout << " " << n << " teams advance" << endl;
            */
            cnt += matches;
            ++round;
        }


        return cnt;
    }
};
