
// 2930. Number of Strings Which Can Be Rearranged to Contain Substring
// https://leetcode.com/problems/number-of-strings-which-can-be-rearranged-to-contain-substring/




/* our base case is n = 4 and having letters l,e,e,t
 * that will give us 12 distinct strings:
 * leet
 * lete
 * ltee
 * tlee
 * elte
 * elet
 * eelt
 * etle
 * tele
 * teel
 * etel
 * eetl
 * the alphabet has obviously 26 distinct lowercase chars, in leet we have 3 already used: l,e,t
 *
 * example n = 5 -> answer 1460
 * we can add 23 other chars to the 12 distinct strings in 5 positions: 23 * 5 * 12
 * then we have char l and char t, which are already present.
 *    adding either l or t to leet:
 *    adding in pos 0 will give us 12 distinct strings
 *    adding in pos 1 will give us  9 more distinct strings (we are loosing 3 where same char are adjacent)
 *    adding in pos 2 will give us  6 more distinct strings ( -"- )
 *    adding in pos 3 will give us  3 more distinct strings ( -"- )
 *    adding in pos 4 will give us  0 more distinct strings ( -"- )
 *    so we are gaining a total of 30 more distinct strings x 2 (l,t)
 * then we have char e, lets add it:
 *    adding in pos 0 will give us 12 distinct strings
 *    adding in pos 1 will give us  6 more distinct strings (we are loosing 6 where same char are adjacent)
 *    adding in pos 2 will give us  2 more distinct strings ( -"- )
 *    adding in pos 3 will give us  0 more distinct strings ( -"- )
 *    adding in pos 4 will give us  0 more distinct strings ( -"- )
 *    so we are gaining a total of 20 more distinct strings x 1 (e)
 * to summarize:
 * 23 * 5 * 12   +   2 * 30   + 1 * 20  = 1460
 *
 */
class Solution {
private:
    unordered_set<string> base{"leet","lete","ltee","tlee","elte","elet","eelt","etle","tele","teel","etel","eetl"};

    pair<unordered_set<string>,int> addchar(char chr, unordered_set<string> b) {
        string s;
        unordered_set<string> us;
        int cnt = 0;
        long l = b.begin()->size();

        // very front
        // cout << "pos 0" << endl;
        for(string t: b) {
            s = "";
            s = s + chr;
            s = s + t;
            auto p = us.insert(s);
            // cout << s << " " << p.second << endl;
        }
        // split
        for(int i = 1; i <= l-1; ++i) {
            // cout << "pos " << i << endl;
            for(string t: b) {
                string p1 = t.substr(0,i);
                string p2 = t.substr(i);
                s = p1;
                s = s + chr;
                s = s + p2;
                auto p = us.insert(s);
                // cout << s << " " << p.second << endl;
            }
        }
        // very end
        // cout << "pos 4" << endl;
        for(string t: b) {
            s = t;
            s = s + chr;
            auto p = us.insert(s);
            // cout << s << " " << p.second << endl;
        }

        // cout << "count " << us.size() << endl;
        return {us,us.size()};
    }

    long mod = 1000000007;

    int mem[100000][2][3][2]; // pos, count of l, e, t

    long rec(int n, int i, int l, int e, int t) {
        // we need to have at least 1 l, 2 e's and 1 t

        if( i == n ) {
            if( l >= 1 && e >= 2 && t >= 1 )
                return 1L;
            else
                return 0L;
        }

        l = min(1,l);
        e = min(2,e);
        t = min(1,t);
        if( mem[i][l][e][t] != -1 )
            return mem[i][l][e][t];

        long ret = 0L;

        // we have a choice
        //    add an l or e or t or
        //    add any other char
        ret = (ret + rec(n, i+1, l+1, e, t)) % mod;             // pick l
        ret = (ret + rec(n, i+1, l, e+1, t)) % mod;             // pick e
        ret = (ret + rec(n, i+1, l, e, t+1)) % mod;             // pick t
        ret = (ret + (23L * rec(n, i+1, l, e, t)) % mod) % mod; // pick any letter other than l, e, t

        return mem[i][l][e][t] = ret;
    }


public:
    int stringCount(int n) {/*
        // adding one more char
        unordered_set<string> t1;
        for(int c = 0; c < 26; ++c) {
            auto p = addchar(c+'a',base);
            for(auto s: p.first)
                t1.insert(s);
        }
        // adding one more char
        unordered_set<string> t2;
        for(int c = 0; c < 26; ++c) {
            auto p = addchar(c+'a',t1);
            for(auto s: p.first)
                t2.insert(s);
        }
        cout << t2.size() << endl;
        */

        if( n < 4 )
            return 0;
        if( n == 4 )
            return 12;

        memset(mem,-1,sizeof mem);
        return rec(n,0,0,0,0);
    }
};
