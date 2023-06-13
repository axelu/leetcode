
// 2682. Find the Losers of the Circular Game
// https://leetcode.com/problems/find-the-losers-of-the-circular-game/




class Solution {
public:
    vector<int> circularGameLosers(int n, int k) {
        vector<bool> seen(n+1,false);
        seen[1] = true;

        int at = 1;
        int f = 1;

        while( true ) {

            at = (at + f * k) % n;
            if( at == 0 )
                at = n;
            if( seen[at] )
                break;

            seen[at] = true;

            ++f;
        }

        vector<int> ans;

        for(int i = 1; i <= n; ++i)
            if( !seen[i] )
                ans.push_back(i);

        return ans;
    }
};
