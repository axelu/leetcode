
// 809. Expressive Words
// https://leetcode.com/problems/expressive-words/




class Solution {
public:
    int expressiveWords(string s, vector<string>& words) {

        vector<pair<char,int>> groups;
        int n = s.size();
        int cnt = 1;
        for(int i = 1; i < n; ++i) {
            if( s[i] == s[i-1] ) {
                ++cnt;
            } else {
                groups.push_back({s[i-1],cnt});
                cnt = 1;
            }
        }
        // finish up
        groups.push_back({s[n-1],cnt});

        /*
        // debug
        for(auto p: groups)
            cout << p.first << ":" << p.second << " ";
        cout << endl;
        */

        int ans = 0;
        int grp_sz = groups.size();
        for(string& word: words) {

            if( word[0] != groups[0].first )
                continue;

            bool is_stretchy = true;
            int grp_idx = 0;
            int wrd_sz = word.size();
            int cnt = 1;
            for(int i = 1; i < wrd_sz; ++i) {
                if( word[i] == word[i-1] ) {
                    ++cnt;
                } else {
                    // we have a group in word
                    if( cnt  > groups[grp_idx].second ||
                        (groups[grp_idx].second < 3 && cnt != groups[grp_idx].second) ) {

                        is_stretchy = false;
                        break;
                    }

                    cnt = 1;
                    ++grp_idx;
                    if( grp_idx == grp_sz || word[i] != groups[grp_idx].first ) {
                        is_stretchy = false;
                        break;
                    }
                }
            }
            // finish up
            if( is_stretchy )
                if( grp_idx != grp_sz-1 ||
                    cnt  > groups[grp_sz-1].second ||
                    (groups[grp_sz-1].second < 3 && cnt != groups[grp_sz-1].second) ) {

                    is_stretchy = false;
                }

            if( is_stretchy )
                ++ans;
        }

        return ans;
    }
};
