
// 2981. Find Longest Special Substring That Occurs Thrice I
// https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i/





class Solution {
public:
    int maximumLength(string s) {
        int n = s.size(); // 3 <= s.length <= 50

        vector<int> freq[26];
        int cnt = 1;
        for(int i = 1; i < n; ++i) {
            if( s[i] != s[i-1] ) {
                freq[s[i-1]-'a'].push_back(cnt);
                cnt = 1;
            } else {
                ++cnt;
            }
        }
        // finish up
        freq[s[n-1]-'a'].push_back(cnt);

        int ans = -1;

        for(int i = 0; i < 26; ++i) {
            if( freq[i].empty() )
                continue;

            sort(freq[i].begin(),freq[i].end(),greater<int>());

            /*
            // debug
            cout << (char)i+'a' << " ";
            for(int x: freq[i] )
                cout << x << " ";
            cout << endl;
            */

            if( freq[i].size() <= 2 && freq[i][0] == 1 )
                continue;

            // solution with the longest consecutive occurence of current char
            if( freq[i][0] > 2 ) {
                ans = max(ans, freq[i][0] - 2);
            }

            // solution with the two longest consecutive occurences of current char
            if( freq[i].size() >= 2 ) {
                int t = min(freq[i][0]-1, freq[i][1]);
                ans = max(ans, t);
            }

            // solution with the three longest consecutive occurences of current char
            if( freq[i].size() >= 3 ) {
                ans = max(ans, freq[i][2]);
            }
        }

        return ans;
    }
};
