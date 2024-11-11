
// 3292. Minimum Number of Valid Strings to Form Target II
// https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-ii/






// see https://www.baeldung.com/cs/rabin-karp-algorithm for Rabin Karp with modulus to also get hash of any substring

// initialize once
unsigned long long p_pow[50001];
bool initialized = false;

class Solution {
private:
    const int p = 31;
    // const int m = 1e9 + 9;

    set<unsigned long long> prefix_hashes;
    unsigned long long h[50001];

    // binary search
    int search(string& target, int i, int s, int e) {
        // finds the longest substring starting at index i (target[i..j]) that has a hash present in the Prefix HashSet.

        // i is the fix starting point in our target
        // s = 0 means we don't even have target[i] char as a prefix in words
        // initial call would be i + e - 1 = target.size()-1
        // example target_size = 14
        // 01234567890123
        //   i
        // s = 1, e = 12 initial call to our search

        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        // the substring of target starting at i with a length of mid, respectively target[i...i+mid-1] is under investigation
        // hash of substring target[i...i+mid-1], "normalized" as if it would be starting at index 0
        unsigned long long h_s;
        if( i > 0 )
            h_s = h[i+mid-1] - (h[i-1] * p_pow[(i+mid-1)-(i-1)]);
        else
            h_s = h[mid-1];

        if( prefix_hashes.find(h_s) != prefix_hashes.end() ) {
            // can we do better?
            int t = search(target, i, mid+1, e);
            return t != -1 ? t : mid;
        }

        return search(target, i, s, mid-1);
    }

    int t[200000]; // segment tree min, lazy propagation
    bool marked[200000];

    void push(int v) {
        if (marked[v]) {
            t[v*2] = min(t[v*2], t[v]);
            t[v*2+1] = min(t[v*2+1], t[v]);
            marked[v*2] = marked[v*2+1] = true;
            marked[v] = false;
        }
    }

    // range assignment
    void update(int v, int tl, int tr, int l, int r, int new_val) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            t[v] = min(t[v], new_val);
            marked[v] = true;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), new_val);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, new_val);
            t[v] = min(t[v*2], t[v*2+1]);
        }
    }

    // range query
    int get_min(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 50001;
        if (l == tl && r == tr) {
            return t[v];
        }
        push(v);
        int tm = (tl + tr) / 2;
        return min(get_min(  v*2,   tl, tm,            l, min(r, tm)),
                   get_min(v*2+1, tm+1, tr, max(l, tm+1),         r));
    }



public:
    int minValidStrings(vector<string>& words, string target) {
        if( !initialized ) {
            initialized = true;
            p_pow[0] = 1ULL;
            for(int i = 1; i < 50001; ++i)
                p_pow[i] = p_pow[i-1] * p;
        }

        // hash every possible prefix Rabin-Karp
        // we could build a Trie and do a dfs to create all prefix hashes
        // for now just doing one word after the other
        for(int i = 0; i < words.size(); ++i) {
            int word_sz = words[i].size(); // cout << "word i" << i << " size " << word_sz << endl;
            unsigned long long h_s = words[i][0]-'a'+1;
            prefix_hashes.insert(h_s);
            for(int j = 1; j < word_sz; ++j) {
                h_s = (h_s * p) + (words[i][j]-'a'+1);
                prefix_hashes.insert(h_s);
            }
        }

        // hash target h[i] is hash[0...i]
        int n = target.size(); cout << n << endl;
        h[0] = target[0]-'a'+1;
        for(int i = 1; i < n; ++i)
            h[i] = (h[i-1] * p) + (target[i]-'a'+1);


        // segment tree
        // init - its a minimum segment tree, so all segments init to max
        for(int i = 0; i < 4*n; ++i)
            t[i] = 50001;
        memset(marked,false,sizeof marked);

        // binary search to find the longest substring starting at index i (target[i..j]) that has a hash present in the HashSet.
        for(int i = n-1; i >= 0; --i) {

            int t = search(target, i, 1, n-i);
            // cout << i << " " << t << endl;

            // if t == -1 then there is no word in words that has a prefix starting at i
            // said differently: there is no word in words that starts with the char at target[i]

            if( t == -1 ) {
                // do nothing
            } else if( i + t == n ) {
                // cout << "we can reach the end from i " << i << endl;
                // update(1, 0, n-1, i, n-1, 1);
                update(1, 0, n-1, i, i, 1);
                // cout << "after update " << get_min(1, 0, n-1, i, n-1) << endl;
            } else {
                // get min
                int mn = get_min(1, 0, n-1, i+1, i+t);
                // cout << "mn " << i+1 << "..." << i+t << " = " << mn << endl;
                // cout << "updating " << i << "..." << i+t-1 << " to " << min(mn+1, 50001) << endl;
                // update(1, 0, n-1, i, i+t-1, min(mn+1, 50001));
                update(1, 0, n-1, i, i, min(mn+1, 50001));
            }

        }

        int ans = get_min(1, 0, n-1, 0, 0); // cout << ans << endl;
        return ans != 50001 ? ans : -1;
    }
};
