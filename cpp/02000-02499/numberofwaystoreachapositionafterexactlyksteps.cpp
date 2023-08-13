
// 2400. Number of Ways to Reach a Position After Exactly k Steps
// https://leetcode.com/problems/number-of-ways-to-reach-a-position-after-exactly-k-steps/




/*      1 2 3 4 5 6 7 8
 *      s     e          s to e takes 3 steps ( 4 - 1 = 3 )
 * example s = 2, e = 5, k = 10 => ans = 0
 *        s     e
 */
class Solution {
private:
    long mod = 1000000007;
    long mem[1001][1001];

    long rec(int pos, int endPos, int mx, int k) {
        if( pos == endPos && k == 0 )
            return 1L;
        if( abs(pos - endPos) == k )
            return 1L;

        if( mem[pos][k] != -1 )
            return mem[pos][k];

        long ans = 0;

        // we have a choice
        //   go right aka up
        //   go left aka down

        if( pos < mx ) {
            ans = (ans + rec(pos+1,endPos,mx,k-1)) % mod;
        }
        if( pos > 0 ) {
            ans = (ans + rec(pos-1,endPos,mx,k-1)) % mod;
        }

        return mem[pos][k] = ans;
    }

public:
    int numberOfWays(int startPos, int endPos, int k) {
        int dist = abs(endPos - startPos);

        if( dist > k )
            return 0;
        if( dist == k )
            return 1;
        if( (dist % 2 == 0 && k % 2 == 1) ||
            (dist % 2 == 1 && k % 2 == 0) )
            return 0;

        // shift start and end, so that we are not in the negatives
        int mn = min(startPos,endPos) - ((k - dist) / 2);
        int mx = max(startPos,endPos) + ((k - dist) / 2);
        // cout << "before shift mn " << mn << " mx " << mx << endl;
        int offset = mn * -1;
        mn += offset;
        mx += offset;
        // cout << "after shift  mn " << mn << " mx " << mx << endl;
        startPos += offset;
        endPos += offset;
        // cout << "after shift s " << startPos << " endPos " << endPos << endl;

        memset(mem,-1,sizeof mem);

        return rec(startPos,endPos,mx,k);
    }
};
