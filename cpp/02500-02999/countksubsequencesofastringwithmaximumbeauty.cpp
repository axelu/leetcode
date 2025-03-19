
// 2842. Count K-Subsequences of a String With Maximum Beauty
// https://leetcode.com/problems/count-k-subsequences-of-a-string-with-maximum-beauty/






class Solution {
private:
    const long mod = 1000000007;

    // 0 <= pos < 26, 0 <= k < 26
    // vector<vector<pair<long,long>>> mem;

    pair<long,long> rec(vector<int>& f, int pos, int k, vector<vector<pair<long,long>>>& mem) {
        if( k == 0 )
            return {0LL,1LL};

        if( mem[pos][k].first != -1LL )
            return mem[pos][k];

        // k is the picks we still have to make
        // if there are only k elements left in f including us,
        //     we don't have a choice, but we have to pick us
        // we have a choice
        //     don't pick me OR
        //     pick me


        // pick
        pair<long,long> a = rec(f, pos+1, k-1, mem);
        a.first = a.first + (long long)f[pos];
        a.second = (a.second * (long long)f[pos]) % mod;

        // don't pick if we can
        pair<long,long> b = {-1,-1};
        int rem = f.size() - pos;
        if( rem > k ) {
            b = rec(f, pos+1, k, mem);
        }

        if( a.first > b.first ) {
            return mem[pos][k] = a;

        } else if( a.first < b.first ) {
            return mem[pos][k] = b;

        } else { // a.first == b.first
            // add the combinations of both options!!!
            int comb = (a.second + b.second) % mod;
            return mem[pos][k] = {a.first, comb};
        }
    }



public:
    int countKSubsequencesWithMaxBeauty(string s, int k) {
        if( k > 26 )
            return 0;

        int cnt[26];
        memset(cnt,0,sizeof cnt);
        int unique = 0;
        for(char c: s) {
            ++cnt[c-'a'];
            if( cnt[c-'a'] == 1 )
                ++unique;
        }
        // how many unique chars do we have in s?
        // let unique be the number of distinct chars in string
        // if unique < k, then there is no answer
        if( k > unique )
            return 0;

        // which combination(s) of chars get us max score?
        //     pick k out of unique
        // once we have that, we can determine how many we can make

        vector<int> f;
        for(int i = 0; i < 26; ++i)
            if( cnt[i] != 0 )
                f.push_back(cnt[i]);

        vector<vector<pair<long,long>>> mem(26,vector<pair<long,long>>(27,{-1,-1}));
        return rec(f, 0, k, mem).second;
    }
};
