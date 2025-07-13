
// 3503. Longest Palindrome After Substring Concatenation I
// https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-i/






class Solution {
private:
    // adopted from 5. Longest Palindromic Substring https://leetcode.com/problems/longest-palindromic-substring/
    pair<vector<int>,int> longestPalindrome(string& s) {
        // returns a pair of a vector<int> v and integer mx
        // vector<int> v of s.size() where v[i] is the length of the longest palindrome starting at i
        // integer mx is the length of the longest Palindrome in s

        size_t n = s.size();

        vector<int> v(n+1,1);
        v[n] = 0;
        int mx = 1;

        if( n == 1 ) {
            return {v,1};
        }
        if( n == 2 ) {
            if( s[0] == s[1] ) {
                v[0] = 2;
                return {v,2};
            } else {
                return {v,1};
            }
        }

        int mem[30][30];
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                mem[i][j] =  i == j ? 1 : 0;

        // sliding over string with length 2 to N
        int b,e,lb = n-1;
        for(int l = 2; l <= n; ++l) {
            for(int i = 0; i <= n-l; ++i) {
                if( l == 2 && s[i] == s[i+1] ) {
                    mem[i][i+1] = 1;
                    mx = l;
                    lb = i;
                    v[i] = l;
                    continue;
                }
                b = i+1;
                e = i+l-2;
                if( s[i] == s[i+l-1] && mem[b][e] ) {
                    mem[i][i+l-1] = 1;
                    mx = l;
                    lb = i;
                    v[i] = l;
                }
            }
        }

       return {v,mx};
    }

    struct Trie {
        struct Trie* children[26];
        int endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = -1;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string& s, vector<int>& v, int i, Trie* dic) {
        struct Trie* tn = dic;

        for(; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if(!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
            tn->endOfWord = max(tn->endOfWord, v[i+1]);
        }

        // last node is end of word
        // ++tn->endOfWord;
    }

    int ans;

    void search(string& s, vector<int>& v, int i, Trie* dic) {
        struct Trie* tn = dic;

        int l = 1;
        for(; i < s.length(); ++i, ++l) {
            int idx = s[i] - 'a';
            if(!tn->children[idx])
                break;

            tn = tn->children[idx];

            // we made it l into both strings
            // so our answer is at least 2 * l
            // but there could be a palindrome starting at either

            // length of palindrome starting in s at the next position
            int sp =  tn->endOfWord;
            // length of palindrome starting in t at the next position
            int st = v[i+1];

            ans = max(ans, (2 * l) + max(sp, st));
        }

        return;
    }


public:
    int longestPalindrome(string s, string t) {
        int s_sz = s.size(); //  1 <= s.length, t.length <= 30
        int t_sz = t.size();

        // get longest palindrome from s and t individually
        auto ps = longestPalindrome(s);
        reverse(t.begin(),t.end());
        auto pt = longestPalindrome(t);

        // cout << "longest Palindrome in s            " << ps.second << endl;
        // cout << "longest Palindrome in t (reversed) " << pt.second << endl;

        ans = max(ps.second, pt.second);

        // now we try to get a better answer by concatenating
        Trie* root = init();
        for(int i = 0; i < s_sz; ++i)
            add(s, ps.first, i, root);

        for(int i = 0; i < t_sz; ++i) {
            search(t, pt.first, i, root);
            /*
            auto p = search(t, pt.first, i, root);
            int post = p.first;
            int poss = p.second;

            cout << "i " << i << " ";
            for(int j = i; j < t_sz; ++j)
                cout << t[j];
            cout << " pos in t " << post << " pos in s " << poss;

            if( post != -1 ) {
                int len_in_t = post - i + 1;
                int len_in_s = len_in_t; // must be the same
                int a = len_in_t + len_in_s;

                // if we are not at the end of s or t respectively,
                // then we can add the longer palindrome starting at the next
                // position of s or t respectively
                int extension = 0;
                if( post != t_sz-1 )
                    extension = pt.first[post+1];
                if( poss != s_sz-1 )
                    extension = max(extension, ps.first[poss+1]);

                cout << " a " << a << " extension " << extension;

                ans = max(ans, a + extension);
            }
            cout << endl;
            */
        }

        return ans;
    }
};




// sample test string pairs
/*

"a"
"a"
"abc"
"def"
"b"
"aaaa"
"abcde"
"ecdba"
"a"
"b"
"abc"
"cba"
"aaaa"
"b"
"caabaa"
"d"
"hc"
"jooh"
"k"
"uryuggfgkp"
"dfgimwcmrr"
"bmh"
"nn"
"avjw"

*/
