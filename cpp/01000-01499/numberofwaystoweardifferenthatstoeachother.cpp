
// 1434. Number of Ways to Wear Different Hats to Each Other
// https://leetcode.com/problems/number-of-ways-to-wear-different-hats-to-each-other/


class Solution {
private:
    long mod = 1000000007;

    long rec(int& n, int& mask, int i, int _hats[][40], int mem[][40]) {
        // if everyone is wearing a hat, we are done
        if( mask == 0 )
            return 1;

        // not everyone is wearing a hat, but there are no more hats
        if( i == 40 )
            return 0;

        if( mem[mask][i] != -1 )
           return mem[mask][i];

        // we have a choice
        // ignore the current hat i OR
        // put hat i on every person who owns it and does not wear a hat yet

        long ret = rec(n,mask,i+1,_hats,mem);

        for(int k = 0; k < n; ++k) {
           if( ((mask >> k) & 1) &&  _hats[k][i] ) {
                mask &= ~(1 << k);  // clear bit
                ret = (ret + rec(n,mask,i+1,_hats,mem)) % mod;
                // backtrack
                mask |= 1 << k;     // set bit
           }
        }

        return mem[mask][i] = ret;
    }

public:
    int numberWays(vector<vector<int>>& hats) {
        int n = hats.size(); // number of people

        // transforming hats into 2D array for quick lookup
        // zero indexing hats
        int _hats[n][40];memset(_hats,0,sizeof _hats);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < hats[i].size(); ++j)
                _hats[i][hats[i][j]-1] = 1;

        // mem: bitmask of people wearing a hat, hat idx
        int t = pow(2,n)-1;
        int mem[t+1][40];memset(mem,-1,sizeof mem);

        // initially, every one is available to wear a hat
        int mask = t;

        // starting with hat 0
        return rec(n,mask,0,_hats,mem);
    }
};


/*
// correct result but too slow
class Solution {
private:
    // debug
    void printBinary(long x) {
        for(int i = 40; i >= 0; --i) {
            if( x & (1L << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }

    long mod = 1000000007;
    unordered_map<long,int> mem;

    long rec(vector<vector<int>>& hats, int& n, int i, long& mask) {
        // cout << "i " << i << " ";printBinary(mask);cout << endl;
        if( i == n )
            return 1L;

        long key = mask + ((long)i << 41);
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        // we have a choice to wear an available hat that we prefer
        // if there is no hat that we prefer available, then this is not a solution

        long ans = 0L;

        for(int k = 0; k < hats[i].size(); ++k) {
            int hatId = hats[i][k];
            if( (mask >> hatId) & 1L ) {
                mask &= ~(1L << hatId);

                ans = (ans + rec(hats,n,i+1,mask)) % mod;

                // backtrack
                mask |= 1L << hatId;
            }
        }

        mem.insert({key,ans});
        return ans;
    }

public:
    int numberWays(vector<vector<int>>& hats) {
        int n = hats.size(); // number of people

        // mask is a bitmask
        // from the right bit 1-40 initially marked as 1, meaning hat available
        // bit 0 (right most bit) not used
        long mask = 2199023255550; // binary 11111111111111111111111111111111111111110
        return rec(hats,n,0,mask);
    }
};
*/
