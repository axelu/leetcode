
// 1639. Number of Ways to Form a Target String Given a Dictionary
// https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/




class Solution {
private:
    long mod = 1000000007;

    long mem[1000][1000];

    long rec(long cnt[][26], int wl, string& target, int tgt_sz, int i, int k) {
        // i = index in target
        // k = we can only search for chars in words with index > k

        //cout << "rec i " << i << " k " << k << endl;

        if( i == tgt_sz )
            return 1;

        if( k == wl )
            return 0;

        if( mem[i][k] != -1 )
           return mem[i][k];

        char c = target[i];

        // counting the number of ways we can create the current char in target
        // by moving further in the position of words
        long a = rec(cnt,wl,target,tgt_sz,i,k+1);

        // if the current char exists in our words, then the number of ways is
        // the product of the count of the current char in words at k and
        // then number of ways that the rest of target can be created
        long b = 0;
        if( cnt[k][c-'a'] > 0 )
            b = (cnt[k][c-'a'] * rec(cnt,wl,target,tgt_sz,i+1,k+1));

        return mem[i][k] = (a + b) % mod;
    }


public:
    int numWays(vector<string>& words, string target) {
        // 1 <= words.length <= 1000
        // 1 <= words[i].length <= 1000, all strings in words have the same length

        int n      = words.size();
        int wl     = words[0].size();
        int tgt_sz = target.size();

        long cnt[wl][26];memset(cnt,0,sizeof cnt); // count of char at pos -> [pos][char]
        for(string& s : words)
            for(int i = 0; i < wl; ++i)
                ++cnt[i][s[i]-'a'];

        memset(mem,-1,sizeof mem);

        return rec(cnt,wl,target,tgt_sz,0,0);
    }
};
