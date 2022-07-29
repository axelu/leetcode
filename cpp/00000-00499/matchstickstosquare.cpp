
// 473. Matchsticks to Square
// https://leetcode.com/problems/matchsticks-to-square/
// https://leetcode.com/explore/challenge/card/june-leetcoding-challenge-2021/605/week-3-june-15th-june-21st/3780/



// original solution (dfs) passed 6/15/2021, but when it became a daily challenge
// 7/11/2022 new test cases had been added and it failed with TLE on 186/195
// added dfs2 that passed




class Solution {
private:
    // debug
    void printMask(int mask, int n) {
        for(int i = n+1; i >= 2; --i) {
            if( mask & (1 << i) ) cout << 1;
            else cout << 0;
        }
    }

    long sides[4];

    bool dfs(vector<int>& matchsticks, int n, int side, long sum, long target,
             int& mask, unordered_set<int>& seen) {

        if( side == 3 ) {
            // there has to be at least one unseen matchstick
            for(int i = 0; i < n; ++i)
                if( !((mask >> (n+1-i)) & 1U) )
                    return true;
            return false;
        }

        for(int i = 0; i < n; ++i) {
            if( (mask >> (n+1-i)) & 1U )
                continue;

            if( sum + (long)matchsticks[i] > target )
                continue;

            mask |= 1UL << (n+1-i);

            if( sum + (long)matchsticks[i] == target ) {
                // current side is a 4th of overall length
                // hence move on to the next side
                // cout << "moving to next side " << side+1 << endl;
                // printMask(mask,n);cout << endl;
                ++mask;

                if( !seen.count(mask) ) {
                    // cout << "moving to next side " << side+1 << endl;
                    // printMask(mask,n);cout << endl;
                    seen.insert(mask);
                    if( dfs(matchsticks,n,side+1,0,target,mask,seen) )
                        return true;
                }

                --mask; // backtrack
            } else {
                // sum + (long)matchsticks[i] < target
                if( dfs(matchsticks,n,side,sum+(long)matchsticks[i],target,mask,seen) )
                    return true;
            }

            // backtrack
            mask &= ~(1UL << (n+1-i));
        }
        return false;
    }

    bool dfs2(vector<int>& matchsticks, int n, int i, long target) {
        if( i == n )
            return sides[0] == sides[1]  && sides[0] == sides[2]  && sides[0] == sides[3] ;

        for(int k = 0; k < 4; ++k) {
            if( sides[k] + (long)matchsticks[i] <= target ) {
                sides[k] += matchsticks[i];
                if( dfs2(matchsticks,n,i+1,target) )
                    return true;
                sides[k] -= matchsticks[i];
            }
        }

        return false;
    }

public:
    bool makesquare(vector<int>& matchsticks) {
        int n = matchsticks.size();
        if( n < 4 ) return false;

        long sum = 0;
        long mx = 0;
        for(int i = 0; i < n; ++i) {
            sum += (long)matchsticks[i];
            mx = max(mx,(long)matchsticks[i]);
        }
        if( sum == 0L ) return false;
        if( sum % 4L != 0L ) return false;
        long target = sum/4L;
        if( mx > target ) return false;

        if( n == 4 ) {
            for(int i = 1; i < 4; ++i)
                if( matchsticks[i-1] != matchsticks[i])
                    return false;
            return true;
        }

        // unordered_set<int> seen;
        // int mask = 0;
        // return dfs(matchsticks,n,0,0,target,mask,seen);

        sides[0] = 0L;
        sides[1] = 0L;
        sides[2] = 0L;
        sides[3] = 0L;
        sort(matchsticks.begin(),matchsticks.end(),greater<int>());
        return dfs2(matchsticks,n,0,target);

    }
};
