#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <deque>
#include <utility>

// 1032. Stream of Characters
// https://leetcode.com/problems/stream-of-characters/

using namespace std;

class StreamChecker {
public:
    StreamChecker(vector<string>& words) {
        dic = init();
        for(string& s : words)
            add(s);
    }
    
    bool query(char letter) {

        bool r = false;

        int pos = 0;
        int vts = vt.size();
        for(int i = 0; i < vts; ++i) {
            Trie* pt = query(vt[pos], letter);
            if( pt ) {
                if( pt->endOfWord ) r = true;
                vt[pos] = pt;
                ++pos;
            } else {
                vt.erase(vt.begin() + pos);
            }
        }
        // single letter test
        Trie* pt = query(dic, letter);
        if( pt ) {
            if( pt->endOfWord ) r = true;
            vt.push_back(pt);
        }

        return r;
    }
private:
    struct Trie {
        struct Trie* children[26];
        bool endOfWord;
    };
    
    Trie* dic;
    vector<Trie*> vt;
    
    struct Trie*  init() {
        struct Trie* tn =  new Trie;
        
        tn->endOfWord = false;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    void add(string& s) {
        struct Trie* tn = dic;

        for (int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = true;
    }

    struct Trie* query(Trie* root, char c) {
        int idx = c - 'a';
        return ( root->children[c - 'a'] ) ? root->children[c - 'a'] : nullptr;
    }
};

int main() {

    vector<string> words = {"cd","f","kl"};
    StreamChecker sc0(words);

    for(auto s : words) cout << s << " ";
    cout << endl;
    vector<char> query = {'a','b','c','d','e','f','g','h','i','j','k','l'};
    for(char c : query) {
        cout << "query " << c << endl; 
        cout << sc0.query(c) << endl;
    }

/*
    words = {"ab","ba","aaab","abab","baa"};
    StreamChecker sc1(words);
    query = {'a','a','a','a','a','b','a','b','a','b','b','b','a','b','a','b','b','b','b','a','b','a','b','a','a','a','b','a','a','a'};
    for(char c : query) {
        cout << "query " << c << endl; 
        cout << sc1.query(c) << endl;
    }
*/
/*
    words = {"abaa","abaab","aabbb","bab","ab"};
    StreamChecker sc2(words);
    query = {'a','a','b','b','b','a','a','b','b','a','a','a','a','b','a','b','b','b','a','b','b','b','a','a','a','a','a','b','a','b','b','b','a','a','b','b','b','a','b','a'};
    for(char c : query) {
        cout << "query " << c << endl; 
        cout << sc2.query(c) << endl;
    }
*/

    words = {"ab","ba","aaab","abab","baa"};
    StreamChecker sc3(words);

    cout << "==========================" << endl;
    for(auto s : words) cout << s << " ";
    cout << endl;
    query = {'a','a','a','a','a','b','a','b','a','b','b','b','a','b','a','b','b','b','b','a','b','a','b','a','a','a','b','a','a','a'};
    for(char c : query) {
        cout << "query " << c << endl; 
        cout << sc3.query(c) << endl;
    }
    


    return 0;
}
