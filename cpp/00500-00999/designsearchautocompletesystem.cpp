
// 642. Design Search Autocomplete System
// https://leetcode.com/problems/design-search-autocomplete-system/





class AutocompleteSystem {
private:
    struct Trie {
        struct Trie* children[27];
        int endOfSentence;
    };

    Trie* dic;
    Trie* localDic;
    string sentence;

    struct cmp {
        public:
        bool operator()(pair<string,int>& l, const pair<string,int>& r) {
            if( l.second < r.second ) {
                return true;
            } else if( l.second == r.second ) {
                int ln = l.first.size();
                int rn = r.first.size();
                int i = 0;
                while( i < ln && i < rn ) {
                    if( l.first[i] != r.first[i] )
                        return l.first[i]>r.first[i];
                    ++i;
                }
                // Note: if we are still here, one sentence is longer than the other,
                //       and the shorter one is a prefix of the longer one
                //       the shorter one wins!
                return ln > rn;
            }
            return false;
        }
    };
    priority_queue<pair<string,int>,vector<pair<string,int>>,cmp> pq;

    Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfSentence = 0;

        for (int i = 0; i < 27; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string& s, int count) {
        struct Trie* tn = dic;

        int idx;
        for(int i = 0; i < s.size(); ++i) {
            idx = s[i] == ' ' ? 26 : s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of sentence
        tn->endOfSentence += count;
    }

    Trie* find(char c) {
        sentence += c;
        if( localDic == nullptr ) return nullptr;
        int idx = c == ' ' ? 26 : c - 'a';
        if( !localDic->children[idx] )
            return nullptr;
        return localDic->children[idx];
    }

    void explore(Trie* root, string& s) {
        if( root->endOfSentence ) {
            pq.push({s,root->endOfSentence});
        }
        for(int i = 0; i < 27; ++i) {
            if( root->children[i] != nullptr ) {
                if( i == 26 ) s += ' ';
                else s += i + 'a';
                explore(root->children[i],s);
                // backtrack
                s.erase(s.size()-1);
            }
        }
    }

public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        dic = init();
        for(int i = 0; i < sentences.size(); ++i)
            add(sentences[i],times[i]);
        localDic = dic;
        sentence = "";
    }

    vector<string> input(char c) {
        vector<string> ans;
        if( c == '#' ) {
            add(sentence,1);

            // reset
            sentence = "";
            localDic = dic;

            return ans;
        }
        localDic = find(c);
        if( localDic == nullptr ) return ans;

        explore(localDic,sentence);

        int i = 0;
        while( !pq.empty() ) {
            if( i < 3 ) ans.push_back(pq.top().first);
            ++i;
            pq.pop();
        }

        return ans;
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */
