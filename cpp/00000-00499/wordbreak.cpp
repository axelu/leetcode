
// day 29 September 2020 challenge
// 139. Word Break
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/558/week-5-september-29th-september-30th/3477/
// https://leetcode.com/problems/word-break/



#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <algorithm>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
private:
    struct Trie {
        struct Trie* children[26];
        bool endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = false;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string& s, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = true;
    }

    bool search(string& s, Trie* dic) {
        struct Trie* tn = dic;

        for (int i = 0; i < s.length(); i++) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                return false;

            tn = tn->children[idx];
        }

        return( tn != NULL && tn->endOfWord );
    }

    bool wordBreak(string s, int dp[], Trie* dic) {
        auto n = s.size();
        for(int i = 1; i <= n; ++i) {
            for(int j = i - 1; j >= 0; --j) {
                string sub = s.substr(j, i - j);
                if (dp[j] && search(sub,dic) ) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if( wordDict.empty() ) return false;

        // init Trie
        Trie* dic = init();
        for(string& s : wordDict)
            add(s, dic);

        auto n = s.size();
        int * dp = new int[n + 1];
        dp[0] = 1; // start
        for (int i = 1; i <= n; ++i)
            dp[i] = 0;

        return wordBreak(s, dp, dic);
    }
};

int main() {

    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> end;
    chrono::duration<double> elapsed_seconds;

    // start = chrono::system_clock::now();
    // do something
    // end = chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    Solution s;
    vector<int> nums;
    string str;
    vector<string> dic;
    bool r;



    str = "leetcode";
    dic = {"leet", "code"};
    cout << str << endl;
    r = s.wordBreak(str,dic);
    cout << "result " << r << endl;
    assert(r == true);

    str = "leetcodeleetcode";
    dic = {"leet", "code","dog"};
    cout << str << endl;
    r = s.wordBreak(str,dic);
    cout << "result " << r << endl;
    assert(r == true);

    str = "leetcodeleetcode";
    dic = {"leetcod", "code","dog","e"};
    cout << str << endl;
    r = s.wordBreak(str,dic);
    cout << "result " << r << endl;
    assert(r == true);

    str = "leetcode";
    dic = {"leetcodea", "dog","cat"};
    cout << str << endl;
    r = s.wordBreak(str,dic);
    cout << "result " << r << endl;
    assert(r == false);

    str = "applepenapple";
    dic = {"apple", "pen"};
    cout << str << endl;
    r = s.wordBreak(str,dic);
    cout << "result " << r << endl;
    assert(r == true);

    str = "catsandog";
    dic = {"cats", "dog", "sand", "and", "cat"};
    cout << str << endl;
    r = s.wordBreak(str,dic);
    cout << "result " << r << endl;
    assert(r == false);

    // case 37/43 initially TLE error
    str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    dic = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    cout << str << endl;
    r = s.wordBreak(str,dic);
    cout << "result " << r << endl;
    assert(r == false);

    // case 40/43 initially TLE error
    str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    dic = {"aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa","ba"};
    cout << str << endl;
    r = s.wordBreak(str,dic);
    cout << "result " << r << endl;
    assert(r == false);

    return 0;
}
