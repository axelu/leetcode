
// 734. Sentence Similarity
// https://leetcode.com/problems/sentence-similarity/




class Solution {
public:
    bool areSentencesSimilar(vector<string>& sentence1, vector<string>& sentence2, vector<vector<string>>& similarPairs) {
        int n1 = sentence1.size();
        int n2 = sentence2.size();
        if( n1 != n2 ) return false;

        unordered_map<string,unordered_set<string>> um;
        pair<unordered_map<string,unordered_set<string>>::iterator,bool> p;
        for(int i = 0; i < similarPairs.size(); ++i) {
            // key by similarPairs[i][0]
            p = um.insert({similarPairs[i][0],{similarPairs[i][1]}});
            if( !p.second )
                p.first->second.insert(similarPairs[i][1]);
            // key by similarPairs[i][1]
            p = um.insert({similarPairs[i][1],{similarPairs[i][0]}});
            if( !p.second )
                p.first->second.insert(similarPairs[i][0]);
        }

        unordered_map<string,unordered_set<string>>::iterator f;
        unordered_map<string,unordered_set<string>>::iterator e = um.end();
        for(int i = 0; i < n1; ++i) {
            if( sentence1[i] == sentence2[i] ) continue;
            f = um.find(sentence1[i]);
            if( f == e || f->second.find(sentence2[i]) == f->second.end() ) return false;
        }

        return true;
    }
};
