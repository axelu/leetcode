
// 884. Uncommon Words from Two Sentences
// https://leetcode.com/problems/uncommon-words-from-two-sentences/



class Solution {
private:
    void getAndCountWords(string& s, unordered_map<string,int>& um) {
        pair<unordered_map<string,int>::iterator,bool> p;
        string word = "";
        for(int i = 0; i < s.size(); ++i) {
            if( s[i] == ' ' ) {
                if( !word.empty() ) {
                    p = um.insert({word,1});
                    if( !p.second )
                        ++p.first->second;
                }
                word = "";
                continue;
            }
            word += s[i];
        }
        // finish up
        if( !word.empty() ) {
            p = um.insert({word,1});
            if( !p.second )
                ++p.first->second;
        }
    }

public:
    vector<string> uncommonFromSentences(string A, string B) {
        unordered_map<string,int> um;
        getAndCountWords(A,um);
        getAndCountWords(B,um);
        vector<string> ans;
        for(auto it = um.begin(); it != um.end(); ++it)
            if( it->second == 1 ) ans.push_back(it->first);
        return ans;
    }
};
