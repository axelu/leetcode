
// 3458. Select K Disjoint Special Substrings
// https://leetcode.com/problems/select-k-disjoint-special-substrings/






class Solution {
private:

    void printBinary(int x) {
        for(int i = 25; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }

    int t[100000]; // segment tree memory efficient indexing
    // each node in the tree holds a mask of the chars that occur
    // in the range the node represents

    int n;
    int first[26];
    int last[26];
    int k;

    void build(string& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = 1<<(a[tl]-'a');
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = t[v+1] | t[v+2*(tm-tl+1)];
        }
    }

    int get(int v, int tl, int tr, int l, int r) {
        // cout << "get v " << v << " tl " << tl << " tr " << tr << " l " << l << " r " << r << endl;
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return get(v+1, tl, tm, l, min(r, tm)) | get(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r);
    }

    int mask_cache[26];

    int build_mask(int c) {
        if( mask_cache[c] != -1 )
            return mask_cache[c];
        int mn = n-1;
        int mx = 0;
        queue<int> q;
        q.push(c);
        bool chckd[26];memset(chckd,false,sizeof chckd);
        chckd[c] = true;
        while( !q.empty() ) {
            c = q.front();
            q.pop();
            mn = min(mn, first[c]);
            mx = max(mx, last[c]);
            int mask = get(1, 0, n-1, first[c], last[c]);
            for(int i = 0; i < 26; ++i) {
                if( mask & (1<<i) && !chckd[i] && (first[i] < mn || last[i]> mx) ) {
                    q.push(i);
                    chckd[i] = true;
                }
            }
        }

        return mask_cache[c] = get(1, 0, n-1, mn, mx);
    }

    unordered_set<int> seen;

    bool rec(int taken, int steps) {
        // cout << "rec taken "; printBinary(taken); cout << " steps " << steps << endl;
        if( steps == k ) {
            if( k != 1 )
                return true;
            // special test for k == 1
            // substring is not the entire string
            int fst = n-1;
            int lst = 0;
            for(int c = 0; c < 26; ++c) {
                if( taken & (1<<c) ) {
                    fst = min(fst, first[c]);
                    lst = max(lst, last[c]);
                }
            }
            return fst != 0 || lst != n-1;
        }

        int key = (taken<<5) + steps;
        if( !seen.insert(key).second )
            return false;

        for(int c = 0; c < 26; ++c) {
            // if we have char c in our string and
            // if we have not taken it yet
            if( first[c] > -1 && !(taken & (1<<c)) ) {
                // we take char c and all chars between
                // its first and last occurence (if any)
                // but only if we can
                int mask = build_mask(c);
                if( taken & mask )
                    continue;
                int taken_new = taken | mask;
                if( rec(taken_new, steps+1) )
                    return true;
            }
        }

        return false;
    }


public:
    bool maxSubstringLength(string s, int k) {
        // 0 <= k <= 26

        if( k == 0 )
            return true;

        n = s.size(); // cout << "n " << n << endl;

        if( k > n )
            return false;

        memset(first,-1,sizeof first);
        memset(last,-1,sizeof last);
        int uniques = 0;
        for(int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            if( first[c] == -1 ) {
                first[c] = i;
                ++uniques;
            }
            last[c] = i;
        }
        /*
        // cout << "uniques " << uniques << endl;
        for(int c = 0; c < 26; ++c)
            cout << (char)(c+'a') << ":" << first[c] << " ";
        cout << endl;
        for(int c = 0; c < 26; ++c)
            cout << (char)(c+'a') << ":" << last[c] << " ";
        cout << endl;
        */

        if( k > uniques )
            return false;

        if( k == n ) {
            // every char can only occur once
            for(int c = 0; c < 26; ++c)
                if( first[c] != last[c] )
                    return false;
            return true;
        }

        build(s, 1, 0, n-1);
        this->k = k;
        // cout << "          zyxwvutsrqponmlkjihgfedcba" << endl;
        memset(mask_cache,-1,sizeof mask_cache);
        return rec(0,0);
    }
};
