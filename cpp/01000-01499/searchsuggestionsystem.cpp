
// 1268. Search Suggestions System
// https://leetcode.com/problems/search-suggestions-system/

// revised version as the solution that passed the problem did have TLE
// when it became a daily challenge
// day 31 May 2021 challenge
// https://leetcode.com/explore/featured/card/may-leetcoding-challenge-2021/602/week-5-may-29th-may-31st/3762/

class Solution {
private:
    struct Trie {
        struct Trie* children[26];
        vector<string> endings;
        // bool endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        // tn->endOfWord = false;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string& s, Trie* tn) {

        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
            tn->endings.push_back(s);
            sort(begin(tn->endings),end(tn->endings));
            if( tn->endings.size() > 3 )
                tn->endings.pop_back();
        }

        // last node is end of word
        // tn->endOfWord = true;
    }
    
    /*
    // DFS
    void getSuggestions(Trie* root, string s, vector<string>& v) {
        if( root->endOfWord ) v.push_back(s);
        if( v.size() == 3 ) return;

        char c;
        for(int i = 0; i < 26; ++i) {
            if( root->children[i] ) {
                c = 'a' + i;
                s += c;
                getSuggestions(root->children[i],s,v);
                // back tracking
                s.pop_back();
                if( v.size() == 3 ) return;
            }
        }
    }
    */

public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        int i;
        
        Trie* dic = init();
        for(i = 0; i < products.size(); ++i) 
            add(products[i],dic);
        
        vector<vector<string>> ans;
        //vector<string> t;
        //string s = "";
        int idx;
        for(char c : searchWord) {
            idx = c-'a';
            dic = dic->children[idx] ? dic->children[idx] : nullptr;
            if( dic == nullptr ) break;
            ans.push_back(dic->endings);
            
            /*
            s += c;
            t.clear();
            getSuggestions(dic,s,t);
            ans.push_back(t);
            */
        }
        while(ans.size()<searchWord.size()) ans.push_back({});
        return ans;
    }
};
