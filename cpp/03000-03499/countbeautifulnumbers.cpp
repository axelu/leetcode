
// 3490. Count Beautiful Numbers
// https://leetcode.com/problems/count-beautiful-numbers/


/*  A positive integer is called beautiful if the product of its digits
    is divisible by the sum of its digits.

    case that number contains one or more 0's:
        the product will be 0, and 0 divides by anything (other than 0)
        so we can derive the number of numbers in our range that contain
        0's separately and add to our result

    as both product and sum are cummutative, the order does not matter
    hence 123, 132, 213, 231, 312, 321 are the same for our purpose
    so once we have a beautiful conmbination of digits, we just need to
    calculate the number of permutations and subtract if any of those are
    less than l or greater than r.
    when calculating number of permutations, beware of repetitions,
    e.g. 17788, meaning size is 5, but distinct objects is 3, 2 distinct
    objects are repeated 2 times
    https://brilliant.org/wiki/permutations-with-repetition/
 */

int factorial[10] = {1,1,2,6,24,120,720,5040,40320,362880};

class Solution {
private:
    vector<int> mn;
    vector<int> mx;
    int mnl, mxl;
    bool discount_at_mnl, discount_at_mxl;

    int get_len(int x) {
        int len = 0;
        while( x ) {
            ++len;
            x /= 10;
        }
        return len;
    }

    vector<int> int2vector(int num) {
        vector<int> ret;
        while( num > 0 ) {
            ret.push_back(num % 10);
            num /= 10;
        }
        reverse(begin(ret),end(ret));
        return ret;
    }

    unordered_map<long,int> mxmem;

    // returns the number of permutations that one can make
    // using state that are greater than mx of the same length as mx
    int recmx(int pos, int state[], bool edge) {
        int len = mx.size();
        if( pos == len )
            return !edge;

        long key = ((long)pos<<41)
                    + ((long)state[0]<<37)
                    + ((long)state[1]<<33)
                    + ((long)state[2]<<29)
                    + ((long)state[3]<<25)
                    + ((long)state[4]<<21)
                    + ((long)state[5]<<17)
                    + ((long)state[6]<<13)
                    + ((long)state[7]<<9)
                    + ((long)state[8]<<5)
                    + ((long)state[9]<<1)
                    + ((long)edge);
        auto f = mxmem.find(key);
        if( f != mxmem.end() )
            return f->second;
        
        int val = mx[pos];

        int ret = 0;

        int i_mn = 0;
        if( pos == 0 || edge )
            i_mn = val;
        

        for(int i = 9; i >= i_mn; --i) {
            if( state[i] == 0 )
                continue;
            
            bool edge_new;
            if( pos == 0 ) {
                if( i > val )
                    edge_new = false;
                else // i == val, will not be below val if pos == 0
                    edge_new = true;
            } else if( !edge ) {
                // something before us is greater, so we will always be greater
                edge_new = false;
            } else {
                // we are so far moving along at the edge
                // if the new val at our position is greater, then 
                // we are no longer moving at the edge
                if( i > val )
                    edge_new = false;
                else // i == val, will not be below val
                    edge_new = true;
            }
            --state[i];
            ret += recmx(pos+1, state, edge_new);
            // backtrack
            ++state[i];

        }

        return mxmem[key] = ret;
    }

    unordered_map<long,int> mnmem;

    // returns the number of permutations that one can make
    // using state that are less than mn of the same length as mn
    int recmn(int pos, int state[], bool edge) {
        int len = mn.size();
        if( pos == len )
            return !edge;

        long key = ((long)pos<<41)
                    + ((long)state[0]<<37)
                    + ((long)state[1]<<33)
                    + ((long)state[2]<<29)
                    + ((long)state[3]<<25)
                    + ((long)state[4]<<21)
                    + ((long)state[5]<<17)
                    + ((long)state[6]<<13)
                    + ((long)state[7]<<9)
                    + ((long)state[8]<<5)
                    + ((long)state[9]<<1)
                    + ((long)edge);
        auto f = mnmem.find(key);
        if( f != mnmem.end() )
            return f->second;
        
        int val = mn[pos];

        int ret = 0;

        int i_mn = pos == 0 ? 1 : 0;
        int i_mx = 9;
        if( pos == 0 || edge )
            i_mx = val;
        
        for(int i = i_mn; i <= i_mx; ++i) {
            if( state[i] == 0 )
                continue;
            
            bool edge_new;
            if( pos == 0 ) {
                if( i < val )
                    edge_new = false;
                else // i == val, will not be greater val if pos == 0
                    edge_new = true;
            } else if( !edge ) {
                // something before us is smaller, so we will always be smaller
                edge_new = false;
            } else {
                // we are so far moving along at the edge
                // if the new val at our position is smaller, then 
                // we are no longer moving at the edge
                if( i < val )
                    edge_new = false;
                else // i == val, will not be greate val
                    edge_new = true;
            }
            --state[i];
            ret += recmn(pos+1, state, edge_new);
            // backtrack
            ++state[i];

        }

        return mnmem[key] = ret;
    }

    int solve0(int len) {
        if( len < 2 )
            return 0;

        // example len = 3
        // first position: 9 choices 1...9
        //   second position: fix to 0 -> 1 choice
        //   third position: 10 choices 0...9
        // then
        //   second position: 9 choices 1...9 (we already did 0)
        //   third position: fix to 0 -> 1 choice
        // 9 * 1 * 10 + 9 * 9 * 1 = 171 
        // example len = 4
        //    fix                   fix                  fix
        // 9 * 1 * 10 * 10 + 9 * 9 * 1 * 10 + 9 * 9 * 9 * 1 = 2439

        int ret = 0;
        for(int i = 2; i <= len; ++i) {
            // position i is fixed to 0
            int before = pow(9,i-1);
            int after = pow(10,len-i);
            ret += before * after;
        }

        return ret;
    }

    // permutations with repetition
    int solve(int state[]) {
        if( state[0] != 0 )
            return 0;

        int n = 0;
        for(int i = 1; i < 10; ++i)
            n += state[i];

        int ret = factorial[n];
        for(int i = 1; i < 10; ++i)
            ret = ret / factorial[state[i]];
        
        return ret;
    }

    // returns the number of beautiful permutations
    // based on finding beautifil combinations
    int rec(const int len, int i, int state[]) {
        int rem = len;  // remaining digits
        for(int j = 0; j < i; ++j)
            rem -= state[j];

        if( rem == 0 ) {
            // get product and sum from state
            int p = 1;
            int s = 0;
            for(int j = 0; j < i; ++j) {
                p *= pow(j,state[j]);
                s += state[j] * j;
            }

            if( s == 0 )
                return 0;

            if( p % s == 0 ) {
                /*
                cout << p << " " << s << " ";
                for(int j = 0; j < 10; ++j)
                    cout << j << ":" << state[j] << " ";
                cout << endl;
                */
                // state represents a beautiful combination
                // how many permutations (permutations with repetition)?
                int t = solve(state);
                if( len == mnl && discount_at_mnl ) {
                    int permutations_less_l = recmn(0, state, false);
                    t -= permutations_less_l;
                }
                if( len == mxl && discount_at_mxl ) {
                    int permutations_greater_r = recmx(0, state, false);
                    t -= permutations_greater_r;
                }
                return t;
            }
            // return p % s == 0;
            return 0;
        }
        if( i > 9 )
            return 0;

        // we have a choice
        // 0 to rem i

        int ret = 0;
        for(int k = 0; k <= rem; ++k) {
            ret += rec(len, i+1, state);
            ++state[i];
        }
        // backtrack
        state[i] = 0;

        return ret;
    }

public:
    int beautifulNumbers(int l, int r) {
        // 1 <= l <= r < 1e9
        // r max 999999999 -> product = 387420489, sum = 81
        //                     INT_MAX 2147483647

        // edge case
        if( l == r ) {
            int p = 1;
            int s = 0;
            while( l ) {
                int rem = l % 10;
                p *= rem;
                s += rem;
                l /= 10;
            }
            return p % s == 0;
        }

        // get min len = number digits in l
        // mnl = get_len(l);
        mn = int2vector(l);
        mnl = mn.size();
        int lb = pow(10,mnl-1);
        discount_at_mnl = false;
        if( lb < l ) {
            // cout << "need to discount below " << l << endl;
            discount_at_mnl = true;
        }

        // get max len = number digits in r
        // mxl = get_len(r);
        mx = int2vector(r);
        mxl = mx.size();
        int ub = pow(10,mxl) - 1;
        discount_at_mxl = false;
        if( ub > r ) {
            // cout << "need to discount above " << r << endl;
            discount_at_mxl = true;
        }

        int ans = 0;
        for(int len = mnl; len <= mxl; ++len) {
            int state[10];memset(state,0,sizeof state);
            int tb = rec(len,0,state);
            // tb will be discounted if applicable, including the permutations w/ 0s !!!
            // even though we have yet to calculate the permutations w/ 0s
            // cout << "len " << len << " beautiful count " << tb << endl;
            ans += tb;
            int t0 = solve0(len);
            // cout << "len " << len << " 0 count         " << t0 << endl;
            ans += t0;
        }

        return ans;
    }
};
