
// 3014. Minimum Number of Pushes to Type Word I
// https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-i/




class Solution {
public:
    int minimumPushes(string word) {
        int ans = 0;
        int presses = 0;
        int n = word.size();
        for(int i = 0; i < n; ++i) {
            if( i % 8 == 0 ) // there are 8 keys we can map
                ++presses;
            ans += presses;
        }

        return ans;
    }
};
