
// 821. Shortest Distance to a Character
// https://leetcode.com/problems/shortest-distance-to-a-character/
// day 7 February 2021 challenge
// https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/584/week-1-february-1st-february-7th/3631/



class Solution {
public:
    vector<int> shortestToChar(string s, char c) {
        // constraints:
        //     1 <= s.length <= 104
        //     c occurs at least once in s
        size_t n = s.size();
        vector<int> ans(n);
        if( n == 1 ) {
            ans[0] = 0;
            return ans;
        }

        int l = string::npos;
        int r = s.find(c);
        int t;
        for(int i = 0; i < n; ++i) {
            if( l == string::npos ) {
                t = r-i;
            } else if( r == string::npos ) {
                t = i-l;
            } else {
                t = min(i-l,r-i);
            }
            ans[i] = t;
            if( t == 0 ) {
                l = i;
                if( i + 1 < n ) r = s.find(c,i+1);
            }
        }
        return ans;
    }
};
