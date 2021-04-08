
// 1629. Slowest Key
// https://leetcode.com/problems/slowest-key/


class Solution {
public:
    char slowestKey(vector<int>& releaseTimes, string keysPressed) {
        char r = keysPressed[0];
        int mx = releaseTimes[0];

        auto n = releaseTimes.size(); // releaseTimes.length == keysPressed.length == n
        int duration;
        for(int i = 1; i < n; ++i) {
            duration = releaseTimes[i] - releaseTimes[i - 1];
            if( duration > mx ) {
                mx = duration;
                r = keysPressed[i];
            } else if( duration == mx ) {
                if( keysPressed[i] > r ) r = keysPressed[i];
            }
        }

        return r;
    }
};
