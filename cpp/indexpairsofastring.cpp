
// 1065. Index Pairs of a String
// https://leetcode.com/problems/index-pairs-of-a-string/ 


class Solution {
public:
    vector<vector<int>> indexPairs(string text, vector<string>& words) {
        int n = text.size();

        vector<vector<int>> ans;

        string word;
        int l,idx;
        for(int i = 0; i < words.size(); ++i) {
            word = words[i];
            l = word.size();
            idx = text.find(word);
            while( idx != string::npos ) {
                ans.push_back({idx,idx+l-1});
                ++idx;
                if( idx > n-l ) break;
                idx = text.find(word,idx);
            }
        }
        sort(ans.begin(),ans.end());
        return ans;
    }
};
