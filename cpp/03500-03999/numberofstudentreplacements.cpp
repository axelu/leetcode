
// 3616. Number of Student Replacements
// https://leetcode.com/problems/number-of-student-replacements/




class Solution {
public:
    int totalReplacements(vector<int>& ranks) {
        int n = ranks.size();
        if( n == 1 )
            return 0;

        int cnt = 0;
        int cur = ranks[0];
        for(int i = 1; i < n; ++i) {
            if( cur > ranks[i] ) {
                cur = ranks[i];
                ++cnt; // a replacement took place
            }
        }

        return cnt;
    }
};
