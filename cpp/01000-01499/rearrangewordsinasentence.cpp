
// 1451. Rearrange Words in a Sentence
// https://leetcode.com/problems/rearrange-words-in-a-sentence/




class Solution {
public:
    string arrangeWords(string& text) {

        vector<pair<string,int>> v;
        stringstream ss(text);
        string s;
        int n = 0;
        while( getline(ss,s,' ') )
            v.push_back({s,n++});

        sort(v.begin(),v.end(),[](pair<string,int>& a, pair<string,int>& b){
            if( a.first.size() < b.first.size() ) {
               return true;
            } else if( a.first.size() == b.first.size() ) {
                if( a.second < b.second ) {
                    return true;
                }
            }
            return false;
        });

        int pos = 0;
        for(int i = 0; i < n; ++i) {

            if( i > 0 )
                text[pos++] = ' ';

            for(int j = 0; j < v[i].first.size(); ++j) {
                if( i == 0 && j == 0 && islower(v[i].first[0]) ) {
                   text[pos++] = v[i].first[j] - 32;
                } else if( i != 0 && j == 0 && isupper(v[i].first[j]) ) {
                    text[pos++] = v[i].first[j] + 32;
                } else {
                   text[pos++] = v[i].first[j];
                }
            }
        }

        return text;
    }
};
