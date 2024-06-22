
// 3168. Minimum Number of Chairs in a Waiting Room
// https://leetcode.com/problems/minimum-number-of-chairs-in-a-waiting-room/



class Solution {
public:
    int minimumChairs(string s) {
        int mx = 0;

        int t = 0;
        for(char c: s) {
            t += c == 'E' ? 1 : -1;
            mx = max(mx, t);
        }

        return mx;
    }
};
