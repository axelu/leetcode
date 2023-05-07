
// 2645. Minimum Additions to Make Valid String
// https://leetcode.com/problems/minimum-additions-to-make-valid-string/



class Solution {
public:
    int addMinimum(string word) {
        int n = word.size();

        int ans = 0;

        int expected = 0; // 0 a, 1 b, c 2
        for(int i = 0; i < n;) {

            if( word[i]-'a' == expected )
                ++i;
            else
                ++ans;

            expected = (expected + 1) % 3;
        }

        // finish up
        if( expected != 0 )
            ans += 3 - expected;

        return ans;
    }
};
