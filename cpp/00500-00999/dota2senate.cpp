
// 649. Dota2 Senate
// https://leetcode.com/problems/dota2-senate/



class Solution {
public:
    string predictPartyVictory(string senate) {
        int n = senate.size();

        queue<int> qD;
        queue<int> qR;
        for(int i = 0; i < n; ++i) {
            if( senate[i] == 'D' ) {
                qD.push(i);
            } else {
                qR.push(i);
            }
        }

        // vote
        for(int i = 0; i <= n; ++i) {
            if( i == n )
                i = 0;

            if( senate[i] == 'D' ) {
                // check if this senator has been banned
                if( qD.empty() || qD.front() != i )
                    continue;
                qD.pop();
                qD.push(i);

                // ban the next R senator from voting
                // of anounce victory if no R senators left
                if( !qR.empty() )
                    qR.pop();
                if( qR.empty() )
                    return "Dire";
            } else {
                // check if this senator has been banned
                if( qR.empty() || qR.front() != i )
                    continue;
                qR.pop();
                qR.push(i);

                // ban the next R senator from voting
                // of anounce victory if no R senators left
                if( !qD.empty() )
                    qD.pop();
                if( qD.empty() )
                    return "Radiant";

            }
        }

        return ""; // satisfy compiler
    }
};
