
// 1904. The Number of Full Rounds You Have Played
// https://leetcode.com/problems/the-number-of-full-rounds-you-have-played/




/* time = "00:00" -> 0
 * time = "23"59" -> 1439
 */

class Solution {
public:
    int numberOfRounds(string loginTime, string logoutTime) {
        // it is garuanteed that loginTime != logoutTime
        // but it could be that loginTime > logoutTime

        int login_hh = stoi(loginTime.substr(0,2));
        int login_mm = stoi(loginTime.substr(3,2));
        int login = login_hh * 60 + login_mm;

        // identify the 1st round we can participate in
        int s = login;
        while( s % 15 != 0 )
            ++s;

        int logout_hh = stoi(logoutTime.substr(0,2));
        int logout_mm = stoi(logoutTime.substr(3,2));
        int logout = logout_hh * 60 + logout_mm;

        int ans = 0;

        if( login < logout ) {
            if( s == 1440 ) // login after 23:45 and logout before midnight
                return 0;

            // participate in rounds as long as round[i] endtime < logoutTime
            int round_end = s + 15; // end of round 0
            while( logout >= round_end ) {
                ++ans;
                round_end += 15;
            }

        } else { // login > logout
            // rounds till midnight
            int round_end = s + 15;
            while( round_end <= 1440 ) {
                ++ans;
                round_end += 15;
            }

            // rounds starting at "00:00";
            round_end = 15;
            while( logout >= round_end ) {
                ++ans;
                round_end += 15;
            }
        }

        return ans;
    }
};
