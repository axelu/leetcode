
// 1781. Sum of Beauty of All Substrings
// https://leetcode.com/problems/sum-of-beauty-of-all-substrings/




class Solution {
public:
    int beautySum(string s) {
        int n = s.size();

        int ans = 0;

        // sliding window, let l = window.size()
        // sliding window with l = 1 is useless, because beauty = 0
        // we need to keep track of number of letters in the window
        // if number of letters in the window is 1, is useless, because beauty = 0
        // we need to keep track of min and max count of a given letter in the window

        for(int l = 2; l <= n; ++l) {
            // cout << "l " << l << endl;

            int cnt[26];memset(cnt,0,sizeof cnt); // count of each letter in window
            map<int,int> mp; // count of count; front of map is min count, last of map is max count

            for(int i = 0; i < n; ++i) {
                // cout << "  i " << i << endl;
                int c = s[i] - 'a';

                int t = cnt[c]; // count of current char c before adding it
                if( mp.find(t) != mp.end() ) {
                    --mp[t];
                    if( mp[t] == 0 )
                        mp.erase(t);
                }
                ++mp[t+1];
                ++cnt[c];

                /*
                cout << "    ";
                for(int k = 0; k < 26; ++k)
                    cout << (char)(k+'a') << ":" << cnt[k] << " ";
                cout << endl;
                */

                if( i >= l-1 ) {
                    // cout << "    window long enough " << s.substr(i-(l-1),l) << endl;

                    int mn = mp.begin()->first; //cout << "    mn " << mn << endl;
                    int mx = mp.rbegin()->first;//cout << "    mx " << mx << endl;
                    ans += mx - mn;

                    // remove letter from front of window for our next round
                    int f = s[i-(l-1)] - 'a';
                    t = cnt[f]; // count of 1st char in window before removing it
                    --mp[t];
                    if( mp[t] == 0 )
                        mp.erase(t);
                    if( t-1 > 0 )
                        ++mp[t-1];
                    --cnt[f];
                }
            }
        }

        return ans;
    }
};
