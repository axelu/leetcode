
// 804. Unique Morse Code Words
// https://leetcode.com/problems/unique-morse-code-words/
// day 22 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/567/week-4-november-22nd-november-28th/3540/



class Solution {
private:
    int r;

    string morse[26]{".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

    struct Trie {
        struct Trie* dash;
        struct Trie* dot;
        bool endOfWord;
    };

    struct Trie* dic;

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->dash = nullptr;
        tn->dot = nullptr;
        tn->endOfWord = false;

        return tn;
    }

    void addAndCountUnique(string& s) {
        struct Trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            if( s[i] == '-' ) {
                if( tn->dash == nullptr )
                    tn->dash = init();
                tn = tn->dash;
            } else {
                if( tn->dot == nullptr )
                    tn->dot = init();
                tn = tn->dot;
            }
        }

        // last node is end of word
        if( !tn->endOfWord ) ++r;
        tn->endOfWord = true;
    }

public:
    int uniqueMorseRepresentations(vector<string>& words) {
        size_t n = words.size();
        if( n == 0 ) return 0;
        if( n == 1 ) return 1;

        dic = init();
        r = 0;

        string s;
        for(int i = 0; i < n; ++i) {
            // string in word to morse code
            s = "";
            for(int j = 0; j < words[i].size(); ++j)
                s += morse[words[i][j]-'a'];

            // add string in morse code to dictionary
            addAndCountUnique(s);
        }

        return r;
    }
};
