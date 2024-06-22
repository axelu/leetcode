
// 3160. Find the Number of Distinct Colors Among the Balls
// https://leetcode.com/problems/find-the-number-of-distinct-colors-among-the-balls/





class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        unordered_map<int,int> balls; // ball, color
        unordered_map<int,int> um;    // color, count

        int n = queries.size();
        vector<int> ans(n);
        for(int i = 0; i < n; ++i) {
            int ball  = queries[i][0];
            int color = queries[i][1];

            if( balls[ball] == 0 ) { // works because 1 <= color <= 1e9
                ++um[color];

            } else if( balls[ball] != color ) {
                --um[balls[ball]];
                if( um[balls[ball]] == 0 )
                    um.erase(balls[ball]);
                ++um[color];
            }

            balls[ball] = color;
            ans[i] = um.size();
        }

        return ans;
    }
};
