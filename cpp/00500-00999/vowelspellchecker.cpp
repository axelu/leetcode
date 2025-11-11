
// 966. Vowel Spellchecker
// https://leetcode.com/problems/vowel-spellchecker/


class Solution {
private: 
    string str_tolowernovowel(string s) {
        transform(s.begin(),s.end(),s.begin(),[](char c){
            if( c == 'a' || c == 'A' ||
                c == 'e' || c == 'E' ||
                c == 'i' || c == 'I' ||
                c == 'o' || c == 'O' ||
                c == 'u' || c == 'U') {
              return '*';
            } else {
                return (char)tolower(c); 
            }
        });
        return s;
    }

    bool isvowel(char c) {
        if( c == 'a' || c == 'A' ||
            c == 'e' || c == 'E' ||
            c == 'i' || c == 'I' ||
            c == 'o' || c == 'O' ||
            c == 'u' || c == 'U') {
            return true;
        }
        return false;
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
        int children_sz = dic->children.size();
        for(int i = 0; i < children_sz; ++i)
            if( dic->children[i]->c == c ) {
                child = dic->children[i];
                break;
            }
        return child;
    }

    void add(string& s, Trie* dic, string& o) {
        Trie* tn = dic;

        for(char c: s) {
            Trie* child = getChild(tn, c);
            if( child == nullptr ) {
                child = new Trie(c);
                tn->children.push_back(child);
            }
            tn = child;
        }
        // last node is end of word
        if( tn->endOfWord.empty() ) 
            tn->endOfWord = o;
    }

    // recursive
    bool search_exact(Trie* dic, string& s, int n, int pos, string& t) {
        if( pos == n ) {
            t = dic->endOfWord;
            return !dic->endOfWord.empty();
        }

        char c = s[pos];

        bool ret = false;

        Trie* child = getChild(dic, c);
        if( child != nullptr )
            ret = search_exact(child, s, n, pos+1, t);

        return ret;
    }

    // recursive
    bool search_case_insensitive(Trie* dic, string& s, int n, int pos, string& t) {
        if( pos == n ) {
            t = dic->endOfWord;
            return !dic->endOfWord.empty();
        }

        char c = tolower(s[pos]);

        bool ret = false;

        int children_sz = dic->children.size();
        for(int i = 0; i < children_sz; ++i)
            if( tolower(dic->children[i]->c) == c ) {
                Trie* child = dic->children[i];
                ret = search_case_insensitive(child, s, n, pos+1, t);
                if( ret )
                    break;
            }

        return ret;
    }

public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        // 1 <= wordlist[i].length, queries[i].length <= 7
        Trie* dic[8];
        Trie* dicLowerNoVowel[8];
        for(int i = 0; i < 8; ++i) {
            dic[i] = new Trie();
            dicLowerNoVowel[i] = new Trie();
        }

        for(string& s: wordlist) {
            add(s, dic[s.size()], s);
            string t = str_tolowernovowel(s);
            if( t != s ) 
                add(t, dicLowerNoVowel[s.size()], s);
        }

        int q_sz = queries.size();
        vector<string> ans(q_sz);

        for(int i = 0; i < q_sz; ++i) {
            int s_sz =  queries[i].size();
            string res = "";
            if( search_exact(dic[s_sz], queries[i], s_sz, 0, res) ) {
                ans[i] = res;
            } else if( search_case_insensitive(dic[s_sz], queries[i], s_sz, 0, res) ) {
                ans[i] = res;
            } else {
                string t = str_tolowernovowel(queries[i]);
                if( t != queries[i] &&  search_exact(dicLowerNoVowel[s_sz], t, s_sz, 0, res) )
                    ans[i] = res;
            }      
        }

        return ans;
    }
};
