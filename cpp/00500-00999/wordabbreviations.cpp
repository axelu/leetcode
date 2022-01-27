
// 527. Word Abbreviation
// https://leetcode.com/problems/word-abbreviation/




class Solution {
private:
    struct Trie {
        struct Trie* children[26];
        bool endOfWord;
        vector<int> positions;
        string suffix;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = false;
        tn->positions = {};
        tn->suffix    = "";

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    struct Trie* init(string suffix) {
        struct Trie* tn =  init();
        tn->suffix = suffix;
        return tn;
    }

    void add(string& s, int pos, Trie* dic) {
        struct Trie* tn = dic;

        int n = s.size();
        char lastChar = s[n-1];
        int rem = n-2;

        int idx;
        string suffix;
        for(int i = 0; i < n; ++i) {
            if( rem > 1 )
                suffix = to_string(rem) + lastChar;
            else if( rem == 1 )
                suffix = s.substr(n-2);
            else if( rem == 0 )
                suffix = lastChar;
            else
                suffix = "";

            idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init(suffix);

            tn->children[idx]->positions.push_back(pos);
            tn = tn->children[idx];

            --rem;
        }

        // last node is end of word
        tn->endOfWord = true;
    }

    void dfs(Trie* tn, string& path, vector<string>& ans) {

        for(int i = 0; i < 26; ++i) {
            if( tn->children[i] != NULL ) {
                path.push_back(i+'a');

                if( tn->children[i]->positions.size() == 1 )
                    ans[tn->children[i]->positions[0]] = path+tn->children[i]->suffix;
                else
                    dfs(tn->children[i],path,ans);

                // backtrack
                path.pop_back();
            }
        }
    }

    void del(Trie* tn) {
        for(int i = 0; i < 26; ++i)
            if( tn->children[i] != NULL )
                del(tn->children[i]);
        delete tn;
    }

public:
    vector<string> wordsAbbreviation(vector<string>& words) {
        int n = words.size();

        vector<string> ans(n);

        unordered_map<string,vector<pair<string,int>>> um;
        pair<unordered_map<string,vector<pair<string,int>>>::iterator,bool> p;
        string word,abbr;
        int wn;
        for(int i = 0; i < n; ++i) {
            word = words[i];
            wn   = word.size();

            if( wn <= 3 ) {
                ans[i] = word;
                continue;
            }

            abbr = word[0] + to_string(wn-2) + word[wn-1];
            p = um.insert({abbr,{{word,i}}});
            if( !p.second )
                p.first->second.push_back({word,i});
        }

        string path = "";
        for(auto it = um.begin(); it != um.end(); ++it) {
            if( it->second.size() == 1 ) {
                ans[it->second[0].second] = it->first;
                continue;
            }

            // we have multiple words of the same length that
            // start with the same char and end with the same char
            Trie* root = init();
            for(int i = 0; i < it->second.size(); ++i)
                add(it->second[i].first,it->second[i].second,root);

            dfs(root,path,ans);
            del(root); // free memory
        }

        return ans;
    }
};
