
// 3752. Lexicographically Smallest Negated Permutation that Sums to Target
// https://leetcode.com/problems/lexicographically-smallest-negated-permutation-that-sums-to-target/


class Solution {
private:
    unordered_map<long long,bool> mem;
    int ans[100000];

    bool rec(int i, long long k) {
        // cout << "i " << i << " k " << k << endl;
        if( i == 1 ) {
            if( k == 1 || k == -1 ) {
                ans[i-1] = (-1 * k);
                return true;
            }
            return false;
        }

        long long key = ((long long)i<<33) + k;
        if( mem.find(key) != mem.end() )
            return false;

        // we can evaluate 4 options immediately
        //
        //    i     all rem
        //   neg      neg
        //   neg      pos
        //   pos      neg
        //   pos      pos

        long long mx = (long long)(i-1) * (i-1+1)/2;
        // cout << "i " << i << " k " << k << " mx " << mx << endl;

        if( k-i-mx == 0LL ) {
            for(int j = i; j > 0; --j)
                ans[j-1] = -j;
            return true;
        }
        if( k-i > 0 && k-i-mx < 0 ) {
            if( rec(i-1, k-i) ) {
                ans[i-1] = -i;
                return true;
            }
        }

        if( k-i+mx == 0LL ) {
            ans[i-1] = -i;
            for(int j = i-1; j > 0; --j)
                ans[j-1] = j;
            return true;
        }
        if( k-i <= 0 && k-i+mx > 0 ) {
            if( rec(i-1, k-i) ) {
                ans[i-1] = -i;
                return true;
            }
        }

        if( k+i-mx == 0LL ) {
            ans[i-1] = i;
            for(int j = i-1; j > 0; --j)
                ans[j-1] = -j;
            return true;
        }
        if( k+i >= 0 && k+i-mx < 0 ) {
            if( rec(i-1, k+i) ) {
                ans[i-1] = i;
                return true;
            }
        }

        if( k+i+mx == 0LL ) {
            for(int j = i; j > 0; --j)
                ans[j-1] = j;
            return true;
        }
        if( k+i < 0 && k+i+mx >= 0 ) {
            if( rec(i-1, k+i) ) {
                ans[i-1] = i;
                return true;
            }
        }

        return mem[key] = false;
    }


public:
    vector<int> lexSmallestNegatedPerm(int n, long long target) {
        // worst case n = 100000 => all pos = 5000050000, all neg = -5000050000
        long long ap = (long long)n * (n+1)/2; // all n negative
        long long an = -ap; // all n positive

        if( target < an || target > ap )
            return {};
        if( target == ap ) {
            vector<int> v(n);
            generate(v.begin(), v.end(), [i = 1] () mutable { return i++; });
            return v;
        }
        if( target == an ) {
            vector<int> v(n);
            generate(v.begin(), v.end(), [i = -n] () mutable { return i++; });
            return v;
        }
        if( ap % 2LL != abs(target) % 2LL )
            return {};

        // at this point we know there is a solution
        rec(n, -target);
        vector<int> res(n);
        for(int i = 0; i < n; ++i)
            res[i] = ans[i];
        sort(begin(res),end(res));

        return res;
    }
};
