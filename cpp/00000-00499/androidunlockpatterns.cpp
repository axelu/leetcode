
// 351. Android Unlock Patterns
// https://leetcode.com/problems/android-unlock-patterns/


class Solution {
private:
    int rec(string& pattern, int& used, int rem) {
        // cout << "rec pattern " << pattern << endl;
        if( rem == 0 )
            return 1;

        // last dot
        int src = pattern.back() - '0';

        int ret = 0;
        // we have a choice
        // we can go to any other unused dot
        // if we pass through the center of another dot,
        // it would have to be used already
        for(int j = 1; j <= 9; ++j) {

            if( ((used >> j) & 1) )
                continue;

            if( (src == 1 && j == 3 && !((used >> 2) & 1) ) ||
                (src == 1 && j == 7 && !((used >> 4) & 1) ) ||
                (src == 1 && j == 9 && !((used >> 5) & 1) ) ||
                (src == 2 && j == 8 && !((used >> 5) & 1) ) ||
                (src == 3 && j == 1 && !((used >> 2) & 1) ) ||
                (src == 3 && j == 7 && !((used >> 5) & 1) ) ||
                (src == 3 && j == 9 && !((used >> 6) & 1) ) ||
                (src == 4 && j == 6 && !((used >> 5) & 1) ) ||
                (src == 6 && j == 4 && !((used >> 5) & 1) ) ||
                (src == 7 && j == 1 && !((used >> 4) & 1) ) ||
                (src == 7 && j == 3 && !((used >> 5) & 1) ) ||
                (src == 7 && j == 9 && !((used >> 8) & 1) ) ||
                (src == 8 && j == 2 && !((used >> 5) & 1) ) ||
                (src == 9 && j == 7 && !((used >> 8) & 1) ) ||
                (src == 9 && j == 1 && !((used >> 5) & 1) ) ||
                (src == 9 && j == 3 && !((used >> 6) & 1) ) )
                continue;

            pattern.push_back('0'+j);
            used |= 1 << j;

            ret += rec(pattern,used,rem-1);

            // backtrack
            used &= ~(1 << j);
            pattern.pop_back();
        }

        return ret;
    }

public:
    int numberOfPatterns(int m, int n) {

        int ans = 0;
        string pattern;
        int used = 0;

        for(int i = m; i <= n; ++i) {
            // every number can be the starting point
            // which will make it unique anyway
            for(int j = 1; j <= 9; ++j) {
                pattern.push_back('0'+j);
                used |= 1 << j;

                ans += rec(pattern,used,i-1);

                // backtrack
                used &= ~(1 << j);
                pattern.pop_back();
            }
        }

        return ans;
    }
};
