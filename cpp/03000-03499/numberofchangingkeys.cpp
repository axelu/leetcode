
// 3019. Number of Changing Keys
// https://leetcode.com/problems/number-of-changing-keys/





class Solution {
public:
    int countKeyChanges(string s) {
        int n = s.size();

        int ans = 0;

        char pre = s[0];
        for(int i = 1; i < n; ++i) {
            char c = s[i];
            if( pre == c ||
                pre == c - 32 ||
                pre == c + 32 ) {
                // do nothing
            } else {
                ++ans;
            }
            pre = c;
        }

        return ans;
    }
};
