
// 3039. Apply Operations to Make String Empty
// https://leetcode.com/problems/apply-operations-to-make-string-empty/




class Solution {
public:
    string lastNonEmptyString(string& s) {

        vector<int> indicies[26];

        int n = s.size();
        for(int i = 0; i < n; ++i)
            indicies[s[i]-'a'].push_back(i);

        vector<int> chars;
        int mx = 0;
        for(int i = 0; i < 26; ++i) {
            if( indicies[i].size() > mx ) {
                mx = indicies[i].size();
                chars.clear();
                chars.push_back(indicies[i].back());
            } else if( indicies[i].size() > 0 && indicies[i].size() == mx ) {
                chars.push_back(indicies[i].back());
            }
        }

        sort(chars.begin(),chars.end());

        string ans = "";
        for(int i = 0; i < chars.size(); ++i)
            ans.push_back(s[chars[i]]);

        return ans;
    }
};
