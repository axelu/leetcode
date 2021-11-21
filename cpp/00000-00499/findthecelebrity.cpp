
// 277. Find the Celebrity
// https://leetcode.com/problems/find-the-celebrity/
// day 22 February 2021 challenge bonus question
// https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/587/week-4-february-22nd-february-28th/3648/



/* The knows API is defined for you.
      bool knows(int a, int b); */

class Solution {
private:
    // depth first search dfs
    void dfs(int a, int n, int seen[], int inCnt[], int outCnt[]) {
        if( seen[a] ) return;
        // cout << a << endl;
        seen[a] = 1;

        for(int i = 0; i < n; ++i) {
            if( i == a ) continue;
            if( knows(a,i) ) {
                ++outCnt[a];
                ++inCnt[i];
                dfs(i,n,seen,inCnt,outCnt);
            }
        }
    }
public:
    int findCelebrity(int n) {
        // directed graph with one or more connected components
        // we are looking for a node with no outbound connections and
        //    n-1 inbound connections

        /*
        int seen[n];memset(seen,0,sizeof seen);
        int inCnt[n];memset(inCnt,0,sizeof inCnt);
        int outCnt[n];memset(outCnt,0,sizeof outCnt);

        for(int i = 0; i < n; ++i)
            if( !seen[i] ) dfs(i,n,seen,inCnt,outCnt);

        // debug
        // for(int i = 0; i < n; ++i)
        //     cout << "i " << i << " outCnt " << outCnt[i] << " inCnt " << inCnt[i] << endl;

        for(int i = 0; i < n; ++i)
            if( outCnt[i] == 0 && inCnt[i] == n-1 ) return i;
        return -1;
        */

        int aknowsb[n][n];memset(aknowsb,-1,sizeof aknowsb);
        int celebrity[n];memset(celebrity,-1,sizeof celebrity);
        bool ab;
        // pass 1
        for(int a = 0; a < n; ++a) {
            if( celebrity[a] == 0 ) continue; // we know this cannot be the celebrity
            for(int b = a+1; b < n; ++b) {
                if( celebrity[b] == 0 ) continue;
                ab = knows(a,b);
                if( !ab ) {
                    // a "could" be the celebrity
                    // b cannot be the celebrity
                    celebrity[b] = 0;
                    aknowsb[a][b] = 0;
                } else {
                    // a cannot be the celebrity
                    celebrity[a] = 0;
                    aknowsb[a][b] = 1;
                    break;
                }
            }
        }
        // at this point all nodes that we know for sure are not celebrities are marked as 0
        // in aknowsb we already kept track of the questions we asked up to this point
        // pass 2
        bool isCelebrity;
        for(int a = 0; a < n; ++a) {
            if( celebrity[a] == 0 ) continue; // we know this cannot be the celebrity
            // does our potential celebrity know anyone?
            isCelebrity = true;
            for(int b = 0; b < n; ++b) {
                if( a == b ) continue;
                if( aknowsb[a][b] == 0 ) continue;
                if( aknowsb[a][b] == 1 || knows(a,b) ) {
                    isCelebrity = false;
                    break;
                }
            }
            if( !isCelebrity ) continue;
            // now we need to check that everyone knows our potential celebrity
            for(int b = 0; b < n; ++b) {
                if( b == a ) continue;
                if( aknowsb[b][a] == 1 ) continue;
                if( aknowsb[b][a] == 0 || !knows(b,a) ) {
                    isCelebrity = false;
                    break;
                }
            }
            if( isCelebrity ) return a;
        }

        return -1;
    }
};
