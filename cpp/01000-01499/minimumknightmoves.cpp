
// 1197. Minimum Knight Moves
// https://leetcode.com/problems/minimum-knight-moves/



class Solution {
public:
    int minKnightMoves(int x, int y) {
        if( x == 0 && y == 0 )
            return 0;

        // eight directions
        int dirR[] = {-2,-1,1,2,2,1,-1,-2};
        int dirC[] = {1,2,2,1,-1,-2,-2,-1};

        unordered_set<long> seen;
        int i,j,i_new,j_new,ans,di,dj,di_new,dj_new;
        queue<array<int,3>> q;
        q.push({0,0,0});
        seen.insert(0);
        long seenIdx;
        while( !q.empty() ) {
            i   = q.front()[0];di = abs(x-i);
            j   = q.front()[1];dj = abs(y-j);
            ans = q.front()[2];
            q.pop();
            // explore all 8 directions
            for(int k = 0; k < 8; ++k) {
                i_new = i + dirR[k]; // TODO check for integer overflow
                // are we getting closer?
                di_new = abs(x-i_new);
                if( di > 5 && di_new > di ) continue;
                j_new = j + dirC[k]; // TODO check for integer overflow
                // are we getting closer?
                dj_new = abs(y-j_new);
                if( dj > 5 && dj_new > dj ) continue;
                if( i_new == x && j_new == y )
                    return ans+1;
                seenIdx  = (unsigned long)i_new<<32;
                seenIdx += (unsigned long)j_new;
                if( seen.find(seenIdx) == seen.end() ) {
                    seen.insert(seenIdx);
                    q.push({i_new,j_new,ans+1});
                }
            }
        }
        return -1; // satisfy compiler
    }
};
