
// 953. Verifying an Alien Dictionary
// https://leetcode.com/problems/verifying-an-alien-dictionary/


class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {

        unordered_map<char,int> um;
        for(int i = 0; i < 26; ++i)
            um.insert({order[i],i});


        vector<string> sorted(words);

        sort(sorted.begin(),sorted.end(),[um](string& l, string& r){

            int ln = l.size();
            int rn = r.size();
            int i = 0;
            while( i < ln && i < rn ) {
                if( l[i] != r[i] ) {
                    if( um.find(l[i])->second < um.find(r[i])->second ) return true;
                    else return false;
                }
                ++i;
            }
            if( i < rn ) return true; // shorter word comes 1st
            return false;
        });
        return sorted == words;
    }
};
