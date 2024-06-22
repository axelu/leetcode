
// 3167. Better Compression of String
// https://leetcode.com/problems/better-compression-of-string/




class Solution {
public:
    string betterCompression(string compressed) {
        int n = compressed.size();

        int freq[26];memset(freq,0,sizeof freq);

        string cnt = "";
        int chr = 0;
        for(int i = 0; i < n; ++i) {
            if( islower(compressed[i]) ) {
                if( !cnt.empty() ) {
                    int t = stoi(cnt);
                    freq[chr] += t;
                }
                cnt = "";
                chr = compressed[i] - 'a';

            } else {
                cnt.push_back(compressed[i]);
            }
        }
        // finish up
        if( !cnt.empty() ) {
            int t = stoi(cnt);
            freq[chr] += t;
        }

        string ans = "";
        for(int i = 0; i < 26; ++i) {
            if( freq[i] != 0 ) {
                char c = 'a' + i;
                ans.push_back(c);

                string t = to_string(freq[i]);
                ans.append(t);
            }
        }

        return ans;
    }
};
