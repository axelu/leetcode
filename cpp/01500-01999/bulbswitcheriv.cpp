
// 1529. Bulb Switcher IV
// https://leetcode.com/problems/bulb-switcher-iv/



class Solution {
public:
    int minFlips(string target) {
        int ans = 0;

        char state = '0';
        for(int i = 0; i < target.size(); ++i) {
            if( target[i] != state ) {
                ++ans;
                state = target[i];
            }
        }
        return ans;
    }
};
