
// 127. Word Ladder
// https://leetcode.com/problems/word-ladder/
// day 9 January 2021 challenge
// https://leetcode.com/explore/featured/card/january-leetcoding-challenge-2021/580/week-2-january-8th-january-14th/3598/



class Solution {
private:
    struct Trie {
        struct Trie* children[26];
        int endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;
        tn->endOfWord = -1;
        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;
        return tn;
    }

    void add(string& s, Trie* dic, int wordListIdx) {
        struct Trie* tn = dic;
        for(int i = 0; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if (!tn->children[idx])
                tn->children[idx] = init();
            tn = tn->children[idx];
        }
        // last node is end of word
        tn->endOfWord = wordListIdx;
    }

    int search(string& s, Trie* dic) {
        struct Trie* tn = dic;
        for(int i = 0; i < s.length(); i++) {
            int idx = s[i] - 'a';
            if( !tn->children[idx] )
                return -1;
            tn = tn->children[idx];
        }
        return tn != NULL ? tn->endOfWord : -1;
    }

public:
    int ladderLength(string& beginWord, string& endWord, vector<string>& wordList) {

        int start = -1;
        int end = -1;

        // init dictionary
        Trie* dic = init();
        size_t wordListLength = wordList.size();
        for(int i = 0; i < wordListLength; ++i) {
            add(wordList[i],dic,i);
            if( wordList[i] == beginWord ) start = i;
            if( wordList[i] == endWord ) end = i;
        }

        // check if endWord is in wordList
        if( -1 == end ) return 0;
        size_t N = beginWord.size(); // endWord.length == beginWord.length == wordList[i].length
        if( 1 == N ) return 2;       // edge case

        if( -1 == start ) {
            add(beginWord,dic,wordListLength);
            start = wordListLength;
            ++wordListLength;
            wordList.push_back(beginWord);
        }

        // init graph
        vector<int> G[wordListLength];
        string t;
        char oldChar,newChar;
        vector<int> neighbors;
        int neighbor;
        int seen[wordListLength];
        for(int i = 0; i < wordListLength; ++i) {
            neighbors.clear();
            t = wordList[i];
            for(int j = 0; j < N; ++j) {
                oldChar = t[j];
                for(int k = 0; k < 26; ++k) {
                    newChar = 'a'+k;
                    if( newChar == oldChar ) continue;
                    t[j] = newChar;
                    // is our new word in the dictionary?
                    neighbor = search(t,dic);
                    if( -1 == neighbor ) continue;
                    neighbors.push_back(neighbor);
                }
                t[j] = oldChar;
            }
            G[i] = neighbors;
            seen[i] = 0;
        }

        // BFS to get shortest path from start to end
        queue<array<int,2>> q;
        q.push({start,1});
        array<int,2> qe;
        while( !q.empty() ) {
            qe = q.front();
            q.pop();

            if( end == qe[0] ) return qe[1];

            seen[qe[0]] = 1;
            neighbors = G[qe[0]];
            for(int i = 0; i < neighbors.size(); ++i) {
                if( seen[neighbors[i]] ) continue;
                q.push({neighbors[i],qe[1]+1});
            }
        }

        return 0;
    }
};
