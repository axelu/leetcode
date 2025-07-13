
// 3579. Minimum Steps to Convert String with Operations
// https://leetcode.com/problems/minimum-steps-to-convert-string-with-operations/






class Solution {
private:
    // function to return min operations to turn s1 into s2
    // TODO use original strings and provide start and end index
    int f(string s1, string s2) {
        int n = s1.size(); // s1.size() == s2.size()

        // edge cases
        if( s1 == s2 )
            return 0;

        // based on hints
        //    first swap pairs
        //        (word1[i], word2[i]) and (word1[j], word2[j])
        //        where word1[i] == word2[j] and word2[i] == word1[j]
        //    the remaining non-matching chars use replace
        //    then try this on the reverse string (one more op)

        // got positions of chars in s2
        vector<int> positions2[26];
        for(int i = 0; i < n; ++i)
            positions2[s2[i]-'a'].push_back(i);

        int a = 0;

        vector<bool> swapped(n,false);
        for(int i = 0; i < n; ++i) {
            if( swapped[i] )
                continue;

            int c1 = s1[i]-'a';
            int c2 = s2[i]-'a';
            if( c1 == c2 )
                continue;

            for(int j: positions2[c1]) {
                if( swapped[j] )
                    continue;
                if( s1[j]-'a' == c2 ) {
                    // swap
                    swapped[i] = true;
                    swapped[j] = true;
                    ++a;
                    break;
                }
            }
            if( !swapped[i] )
                ++a; // replace
        }

        // try on reversed string
        reverse(s1.begin(),s1.end());
        if( s1 == s2 )
            return 1;

        int b = 1;

        swapped.assign(n,false); // reset swapped
        for(int i = 0; i < n; ++i) {
            if( swapped[i] )
                continue;

            int c1 = s1[i]-'a';
            int c2 = s2[i]-'a';
            if( c1 == c2 )
                continue;

            for(int j: positions2[c1]) {
                if( swapped[j] )
                    continue;
                if( s1[j]-'a' == c2 ) {
                    // swap
                    swapped[i] = true;
                    swapped[j] = true;
                    ++b;
                    break;
                }
            }
            if( !swapped[i] )
                ++b; // replace
        }

        return min(a,b);
    }

    int mem[100];

    int rec(string& word1, string& word2, int pos) {
        int n = word1.size(); // word1.size() == word2.size()
        if( pos == n )
            return 0;

        if( mem[pos] != -1 )
            return mem[pos];

        int ret = INT_MAX;

        string s1 = "";
        string s2 = "";
        for(int i = pos; i < n; ++i) {
            s1.push_back(word1[i]);
            s2.push_back(word2[i]);
            int t = f(s1,s2);

            ret = min(ret, t + rec(word1,word2,i+1));
        }

        return mem[pos] = ret;
    }

public:
    int minOperations(string word1, string word2) {
        // cout << f("abcdef", "fedabc") << endl; // expect 2

        /*
        word1 = "qiplzjwptfbceuvqsraxwbrvfkvnlnqexhpyrlomspowjjoddqcbrvwzftorgexdnmcezstrhhpqrdvwvyxottpbmduvhraxdcbc";
        word2 = "mldihmiayqvurmsbxhubehubqlfxzfpoquwaghahxvdojvpheliiudlnqrkqwcepwcpfjrmgppwymnfqbqbvvmindvdcxjttmiyx";
        int tt1n = 100;
        for(int i = 0; i < tt1n; ++i) {
            for(int j = i; j < tt1n; ++j) {
                int l = j - i + 1;
                string s1 = word1.substr(i,l);
                string s2 = word2.substr(i,l);
                f(s1, s2);
            }
        }
        */

        memset(mem,-1,sizeof mem);
        return rec(word1,word2,0);
    }
};
