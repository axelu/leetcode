
// 187. Repeated DNA Sequences
// day 17 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/561/week-3-october-15th-october-21st/3498/
// https://leetcode.com/problems/repeated-dna-sequences/



class Solution {
private:
    struct Trie {
        struct Trie* children[4];
        bool endOfWord;
    };

    struct Trie*  init() {
        struct Trie* tn =  new Trie;
        tn->endOfWord = false;
        for (int i = 0; i < 4; ++i)
            tn->children[i] = NULL;
        return tn;
    }

    bool add(Trie* dic, const int& b, const int& e, string& s) {
        struct Trie* tn = dic;

        bool added = false;
        int idx;
        for (int i = b; i < e; ++i) {
            if( s[i] == 'A' ) {idx = 0;}
            else if( s[i] == 'C' ) {idx = 1;}
            else if( s[i] == 'G' ) {idx = 2;}
            else if( s[i] == 'T' ) {idx = 3;}
            if (!tn->children[idx]) {
                tn->children[idx] = init();
                added = true;
            }

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = true;

        return added;
    }

public:
    vector<string> findRepeatedDnaSequences(string s) {
        auto n = s.size();
        if( n <= 10 ) return {};

        Trie* dic = init();
        add(dic,0,10,s);

        vector<string> r;
        bool added;
        string str;
        for(int i = 1; i <= n-10; ++i) {
            added = add(dic,i,i+10,s);
            if(!added) {
                str = s.substr(i,10);
                auto f = find(begin(r),end(r),str);
                if( f == end(r) ) r.push_back(str);
            }
        }

        return r;
    }
};
