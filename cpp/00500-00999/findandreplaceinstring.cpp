
// 833. Find And Replace in String
// https://leetcode.com/problems/find-and-replace-in-string/




class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {

        int k = indices.size(); // indices.size() == sources.size() == targets.size()
        map<int,pair<string,string>> mp;
        for(int i = 0; i < k; ++i)
            mp[indices[i]] = {sources[i],targets[i]};

        // for(auto it = mp.begin(); it != mp.end(); ++it)
        //     cout << it->first << " " << it->second.first << " " << it->second.second << endl;

        string ans = "";

        int n = s.size();
        auto it = mp.begin();
        for(int i = 0; i < n; ++i) {
            if( it != mp.end() && i == it->first ) {
                int length = it->second.first.size();
                if( s.substr(i,length) == it->second.first ) {
                    ans += it->second.second;

                    i += length -1; // loop will advance i by 1
                } else {
                    ans += s[i];
                }
                ++it;
            } else {
                ans += s[i];
            }
        }

        return ans;
    }
};
