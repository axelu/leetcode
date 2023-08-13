
// 2788. Split Strings by Separator
// https://leetcode.com/problems/split-strings-by-separator/



class Solution {
public:
    vector<string> splitWordsBySeparator(vector<string>& words, char separator) {
        vector<string> ans;

        for(string& word: words) {
            stringstream ss(word);
            string s;
            while( getline(ss,s,separator) )
                if( !s.empty() )
                    ans.push_back(s);
        }

        return ans;
    }
};





