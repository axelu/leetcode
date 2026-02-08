
// 3791. Number of Balanced Integers in a Range
// https://leetcode.com/problems/number-of-balanced-integers-in-a-range/

/*
   high <= 1e15
   012345678901234
   9 9 9 9 9 9 9 9 -> worst case 8*9 = 72
   so for a DP solution, we have the state by
   pos, oddSum, evenSum, lowEdge, topEdge
   16   73      73       2        2       = 341056 states

   // TODO we could just track the difference of oddSum and evenSum


 */
class Solution {
private:
    bool is_balanced(long long n) {
        long long o = 0; // sum of digits at odd positions
        long long e = 0; // sum of digits at even positions
        int p = 1;
        while( n ) {
            long long rem = n % 10LL;
            if( p )
                o += rem;
            else
                e += rem;
            p = !p;
            n /= 10LL;
        }

        return o == e;
    }

    vector<int> int2vector(long long n) {
        vector<int> ret;
        while( n ) {
            int rem = n % 10LL;
            ret.push_back(rem);
            n /= 10LL;
        }
        reverse(begin(ret), end(ret));
        return ret;
    }

    vector<int> lo;
    vector<int> hi;
    int n;

    long long mem[16][73][73][2][2];

    long long rec(int pos, int oddSum, int evenSum, bool le, bool te) {
        if( pos == n )
            return oddSum == evenSum;

        // cout << "rec pos " << pos << " oddSum " << oddSum << " evenSum " << evenSum << " le " << le << " te " << te << endl;

        if( mem[pos][oddSum][evenSum][le][te] != -1 )
            return mem[pos][oddSum][evenSum][le][te];

        long long ret = 0LL;

        // if le we are moving along the low edge
        // if te we are moving along the top edge

        int j_lo = le ? lo[pos] : 0;
        int j_hi = te ? hi[pos] : 9;
        for(int j = j_lo; j <= j_hi; ++j) {
            int oddSum_new  = pos % 2 == 1 ? oddSum + j : oddSum;
            int evenSum_new = pos % 2 == 0 ? evenSum + j: evenSum;
            bool le_new = le && j == j_lo ? true : false;
            bool te_new = te && j == j_hi ? true : false;
            ret += rec(pos+1, oddSum_new, evenSum_new, le_new, te_new);
        }

        return mem[pos][oddSum][evenSum][le][te] = ret;
    }

public:
    long long countBalanced(long long low, long long high) {
        // 1 <= low <= high <= 1e15
        if( high < 10 )
            return 0;
        if( low < 10 )
            low = 10;
        if( low == high )
            return is_balanced(low);

        hi = int2vector(high);
        lo = int2vector(low);
        int lo_sz = lo.size();
        n = hi.size();
        // fill lo with leading 0's
        while( lo.size() < n )
            lo.insert(lo.begin(), 0);

        memset(mem,-1,sizeof mem);
        long long ans = 0LL;
        for(int i = n-lo_sz; i >= 0; --i) {
            // by default we can put 1..9 at pos i
            if( i == n-lo_sz ) {
                // low and high could have same number digits
                if( i == 0 ) {
                    for(int j = lo[i]; j <= hi[i]; ++j) {
                        bool le = j == lo[i];
                        bool te = j == hi[i];
                        ans += rec(i+1, 0, j, le, te);
                    }
                } else {
                    for(int j = lo[i]; j <= 9; ++j) {
                        bool le = j == lo[i];
                        if( i % 2 == 0 )
                            ans += rec(i+1, 0, j, le, false);
                        else
                            ans += rec(i+1, j, 0, le, false);
                    }
                }

            } else if( i == 0 ) {
                for(int j = 1; j <= hi[0]; ++j) {
                    bool te = j == hi[0];
                    ans += rec(i+1, 0, j, false, te);
                }

            } else {
                for(int j = 1; j <= 9; ++j) {
                    if( i % 2 == 0 )
                        ans += rec(i+1, 0, j, false, false);
                    else
                        ans += rec(i+1, j, 0, false, false);
                }
            }
        }

        return ans;
    }
};
