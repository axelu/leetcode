
// 966. Vowel Spellchecker
// https://leetcode.com/problems/vowel-spellchecker/
// day 22 March 2021 bonus challenge
// https://leetcode.com/explore/challenge/card/march-leetcoding-challenge-2021/591/week-4-march-22nd-march-28th/3681/



class Solution {
private:

    string str_tolower(string s) {
        transform(s.begin(),s.end(),s.begin(),[](unsigned char c){
            return tolower(c);
        });
        return s;
    }

    string str_novowel(string s) {
        transform(s.begin(),s.end(),s.begin(),[](char c){
            if( c == 'a' || c == 'A' ||
                c == 'e' || c == 'E' ||
                c == 'i' || c == 'I' ||
                c == 'o' || c == 'O' ||
                c == 'u' || c == 'U') {
              return '*';
            }
            return c;
        });
        return s;
    }

    struct Trie {
        char c;
        vector<Trie*> children;
        string endOfWord;
        Trie() : c('-'), children({}), endOfWord("") {}
        Trie(char c) : c(c), children({}), endOfWord("") {}
    };

    Trie* getChild(Trie* dic, char c) {
        Trie* child = nullptr;
        for(int i = 0; i < dic->children.size(); ++i)
            if( dic->children[i]->c == c ) {
                child = dic->children[i];
                break;
            }
        return child;
    }

    void add(string& s, Trie* dic, string& o) {
        Trie* tn = dic;

        for(int i = 0; i < s.size(); ++i) {
            Trie* child = getChild(tn,s[i]);
            if( child == nullptr ) {
                child = new Trie(s[i]);
                tn->children.push_back(child);
            }
            tn = child;
        }
        // last node is end of word
        if( tn->endOfWord.empty() ) tn->endOfWord = o;
    }

    string search(Trie* dic, string& s) {
        Trie* tn = dic;

        for(int i = 0; i < s.length(); i++) {
            Trie* child = nullptr;
            for(int j = 0; j < tn->children.size(); ++j) {
                if( tn->children[j]->c == s[i] ) {
                    child = tn->children[j];
                    break;
                }
            }
            if( child == nullptr )
                return "";

            tn = child;
        }

        return tn != nullptr && !tn->endOfWord.empty() ? tn->endOfWord : "";
    }

public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {

        Trie* dic = new Trie();
        Trie* dicLowerNoVowel = new Trie();
        string t;
        for(int i = 0; i < wordlist.size(); ++i) {
            t = wordlist[i];
            add(t,dic,wordlist[i]);
            t = str_tolower(wordlist[i]);
            add(t,dicLowerNoVowel,wordlist[i]);
            t = str_novowel(t);
            if( t != wordlist[i]) add(t,dicLowerNoVowel,wordlist[i]);
        }

        int n = queries.size();
        vector<string> ans(n);
        string res;
        for(int i = 0; i < n; ++i) {
            res = search(dic,queries[i]);
            if( !res.empty() ) {
                ans[i] = res;
                continue;
            }
            t = str_tolower(queries[i]);
            if( t != queries[i] ) {
                res = search(dicLowerNoVowel,t);
                if( !res.empty() ) {
                    ans[i] = res;
                    continue;
                }
            }
            t = str_novowel(t);
            ans[i] = search(dicLowerNoVowel,t);
        }
        return ans;
    }
};
