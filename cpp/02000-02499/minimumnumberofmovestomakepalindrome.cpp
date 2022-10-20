
// 2193. Minimum Number of Moves to Make Palindrome
// https://leetcode.com/problems/minimum-number-of-moves-to-make-palindrome/



class Solution {
private:
    int t[8000];

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = tl;
        } else {
            int tm = (tl + tr) / 2;
            build(v*2, tl, tm);
            build(v*2+1, tm+1, tr);
            t[v] = 0;
        }
    }

    void update(int v, int tl, int tr, int l, int r, int add) {
        if (l > r)
            return;
        if (l == tl && r == tr) {
            t[v] += add;
        } else {
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), add);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, add);
        }
    }

    int get(int v, int tl, int tr, int pos) {
        if (tl == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            return t[v] + get(v*2, tl, tm, pos);
        else
            return t[v] + get(v*2+1, tm+1, tr, pos);
    }

public:
    int minMovesToMakePalindrome(string s) {
        int n = s.size();

        deque<int> idxs[26];
        for(int i = 0; i < n; ++i)
            idxs[s[i]-'a'].push_back(i);

        // initially there is a letter at each index
        build(1,0,n-1);

        int ans = 0;

        int i = 0, j = n-1; // physical index in s
        while( i < n && j >= 0 ) {
            //cout << "ans " << ans << endl;
            //cout << "s " << s << endl;
            //cout << "i  " << i << " j  " << j << endl;
            if( s[i] == '#' ) {
                ++i;
                continue;
            } else if( s[j] == '#' ) {
                --j;
                continue;
            } else if( s[i] == s[j] ) {
                if( !idxs[s[i]-'a'].empty() )
                    idxs[s[i]-'a'].pop_front();
                if( !idxs[s[i]-'a'].empty() )
                    idxs[s[i]-'a'].pop_back();
                ++i;--j;
                continue;
            }

            // get virtual index
            int iv = get(1,0,n-1,i);
            int jv = get(1,0,n-1,j);
            //cout << "iv " << iv << " jv " << jv << endl;
            if( iv >= jv )
                break;

            // we can either make s[i] same char as s[j] OR
            //               make s[j] same char as s[i]
            // we will do whatever takes less swaps (greedy)
            int repl_i  = idxs[s[j]-'a'].front();
            int repl_iv = get(1,0,n-1,repl_i);
            int idv     = repl_iv - iv;
            //cout << "repl_i " << repl_i << " repl_iv " << repl_iv << " idv " << idv << endl;
            int repl_j  = idxs[s[i]-'a'].back();
            int repl_jv = get(1,0,n-1,repl_j);
            int jdv     = jv - repl_jv;
            //cout << "repl_j " << repl_j << " repl_jv " << repl_jv << " jdv " << jdv << endl;
            if( idv < jdv ) {
                // pop queue
                idxs[s[j]-'a'].pop_front();
                // replace replacement with #
                s[repl_i] = '#';
                // add to range [i,repli-1] 1
                update(1,0,n-1,i,repl_i-1,1);
                // calculate swaps and add to ans
                ans += repl_iv-iv;
                // 'advanve' j
                idxs[s[j]-'a'].pop_back();
                --j;
            } else {
                // pop queue
                idxs[s[i]-'a'].pop_back();
                // replace replacement with #
                s[repl_j] = '#';
                // add to range [replj+1,j] -1
                update(1,0,n-1,repl_j+1,j,-1);
                // calculate swaps and add to ans
                ans += jv-repl_jv;
                // advanve i
                idxs[s[i]-'a'].pop_front();
                ++i;
            }
        }

        return ans;
    }
};
