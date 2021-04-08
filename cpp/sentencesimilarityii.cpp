
// 737. Sentence Similarity II
// https://leetcode.com/problems/sentence-similarity-ii/



class Solution {
private:
    bool go(string src, string dest, unordered_map<string,vector<string>>& t, unordered_set<string>& seen) {
        if( src == dest ) return true;
        if( !seen.insert(src).second ) return false;

        for(int i = 0; i < t[src].size(); ++i)
            if( go(t[src][i],dest,t,seen) ) return true;

        return false;
    }

public:
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<vector<string>>& pairs) {
        int n1 = words1.size();
        int n2 = words2.size();
        if( n1 != n2 ) return false;

        unordered_map<string,vector<string>> t;
        pair<unordered_map<string,vector<string>>::iterator,bool> p;
        for(int i = 0; i < pairs.size(); ++i) {
            // key by pairs[i][0]
            p = t.insert({pairs[i][0],{pairs[i][1]}});
            if( !p.second )
                p.first->second.push_back(pairs[i][1]);
            // key by pairs[i][1]
            p = t.insert({pairs[i][1],{pairs[i][0]}});
            if( !p.second )
                p.first->second.push_back(pairs[i][0]);
        }

        unordered_set<string> seen;
        unordered_map<string,vector<string>>::iterator f;
        unordered_map<string,vector<string>>::iterator e = t.end();
        for(int i = 0; i < n1; ++i) {
            if( words1[i] == words2[i] ) continue;
            // is words2[i] in our dictionary tree?
            f = t.find(words2[i]);
            if( f == e ) return false;
            // is words1[i] in our dictionary tree?
            f = t.find(words1[i]);
            if( f == e ) return false;
            // are words1[i] and words2[i] connected?
            seen.clear();
            if( !go(words1[i],words2[i],t,seen) ) return false;
        }
        return true;
    }
};
