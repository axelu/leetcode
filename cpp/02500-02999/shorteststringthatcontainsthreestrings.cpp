
// 2800. Shortest String That Contains Three Strings
// https://leetcode.com/problems/shortest-string-that-contains-three-strings/





/* we have 3 strings a, b and c
 * with that we have 6 permutations of how to combine them:
 * 1 a b c
 * 2 a c b
 * 3 b a c
 * 4 b c a
 * 5 c a b
 * 6 c b a
 * we need to find the largest overlap between them:
 * ab, ac, ba, bc, ca, cb
 * example: let a = abc and let b = bca
 *          a abc
 *          b  bca
 *          overlap ab = 2
 * the suffix "bc" of string a overlaps with prefix "bc" of string b
 */
class Solution {
private:
    struct Trie {
        struct Trie* children[26];
        bool endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = false;
        for(int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string& s, int i, Trie* dic, stack<Trie*>& stck) {
        struct Trie* tn = dic;

        for(; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx]) {
                tn->children[idx] = init();
                stck.push(tn->children[idx]);
            }

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = true;
    }

    struct Trie* build_suffix_trie(string& s, stack<Trie*>& stck) {
        Trie* dic = init();
        stck.push(dic);
        for(int i = 0; i < s.size(); ++i)
            add(s,i,dic,stck);
        return dic;
    }

    int overlap(Trie* dic, string& s) { // search
        struct Trie* tn = dic;

        int t = 0;
        int i = 0;
        for(; i < s.length(); i++) {
            int idx = s[i] - 'a';
            if (!tn->children[idx]) {
                return t;

            }
            tn = tn->children[idx];
            if( tn->endOfWord )
                t = i+1;
        }
        // s is a substring
        if( i == s.length() )
            return s.length();

        return t;
    }


public:
    string minimumString(string a, string b, string c) {
        // for each string build a suffix Trie

        stack<Trie*> stck;

        Trie* dic = build_suffix_trie(a,stck);
        int ab = overlap(dic,b);
        int ac = overlap(dic,c);
        // tear down trie because I got Memory Limit Exceeded when submitting, even though it ran find when 'Run Code'
        while( !stck.empty() ) {
            delete(stck.top());
            stck.pop();
        }
        dic = build_suffix_trie(b,stck);
        int ba = overlap(dic,a);
        int bc = overlap(dic,c);
        // tear down trie
        while( !stck.empty() ) {
            delete(stck.top());
            stck.pop();
        }
        dic = build_suffix_trie(c,stck);
        int ca = overlap(dic,a);
        int cb = overlap(dic,b);
        // tear down trie
        while( !stck.empty() ) {
            delete(stck.top());
            stck.pop();
        }

        /*
        cout << "ab " << ab << endl;
        cout << "ac " << ab << endl;
        cout << "ba " << ab << endl;
        cout << "bc " << ab << endl;
        cout << "ca " << ab << endl;
        cout << "cb " << ab << endl;
        */

        vector<string> v;

        string str_ab = a + b.substr(ab);
        string str_ac = a + c.substr(ac);
        string str_ba = b + a.substr(ba);
        string str_bc = b + c.substr(bc);
        string str_ca = c + a.substr(ca);
        string str_cb = c + b.substr(cb);

        // a b c
        if( str_ab == a ) { // b is a substring of a
            v.push_back(str_ac);
        } else {
            string abc = a + b.substr(ab) + c.substr(bc);
            v.push_back(abc);
        }
        // a c b
        if( str_ac == a ) { // c is a substring of a
            v.push_back(str_ab);
        } else {
            string acb = a + c.substr(ac) + b.substr(cb);
            v.push_back(acb);
        }
        // b a c
        if( str_ba == b ) { // a is a substring of b
            v.push_back(str_bc);
        } else {
            string bac = b + a.substr(ba) + c.substr(ac);
            v.push_back(bac);
        }
        // b c a
        if( str_bc == b ) { // c is a substring of b
            v.push_back(str_ba);
        } else {
            string bca = b + c.substr(bc) + a.substr(ca);
            v.push_back(bca);
        }
        // c a b
        if( str_ca == c ) { // a is a substring of c
            v.push_back(str_cb);
        } else {
            string cab = c + a.substr(ca) + b.substr(ab);
            v.push_back(cab);
        }
        // c b a
        if( str_cb == c ) { // b is a substring of c
            v.push_back(str_ca);
        } else {
            string cba = c + b.substr(cb) + a.substr(ba);
            v.push_back(cba);
        }

        /*
        cout << abc << endl;
        cout << acb << endl;
        cout << bac << endl;
        cout << bca << endl;
        cout << cab << endl;
        cout << cba << endl;
        */

        sort(v.begin(),v.end(),[](const string& lhs, const string& rhs){
            if( lhs.size() < rhs.size() ) {
                return true;
            } else if( lhs.size() == rhs.size() ) {
                return lhs < rhs;
            }
            return false;
        });

        return v[0];
    }
};
