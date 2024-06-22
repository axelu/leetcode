
// 2947. Count Beautiful Substrings I
// https://leetcode.com/problems/count-beautiful-substrings-i/



class Solution {
public:
    int beautifulSubstrings(string s, int k) {
        int n = s.size();

        int ans = 0;

        int t[n][2]; // t[i][0] count of vowels starting at i, t[i][1] count of consonants starting at i
        memset(t,0,sizeof t);

        for(int l = 1; l <= n; ++l) {
            // cout << "l " << l << endl;
            int i_max = n-l;
            for(int i = 0; i <= i_max; ++i) {
                int j = i + l - 1;
                // cout << "i " << i << " j " << j << endl;
                if( s[j] == 'a' || s[j] == 'e' || s[j] == 'i' || s[j] == 'o' || s[j] == 'u')
                    ++t[i][0];
                else
                    ++t[i][1];

                // cout << "vowels " << t[i][0] << " consonants " << t[i][1] << endl;

                if( t[i][0] == t[i][1] && (t[i][0] * t[i][1]) % k == 0 )
                    ++ans;
            }
        }

        return ans;
    }
};
