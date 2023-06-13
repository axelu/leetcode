
// 2381. Shifting Letters II
// https://leetcode.com/problems/shifting-letters-ii/




class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        int n = s.size();

        int arr[n+1];memset(arr,0,sizeof arr);

        for(auto& v: shifts) {
            int d = v[2] == 1 ? 1 : -1;
            arr[v[0]] += d;
            arr[v[1]+1] -= d;
        }

        int k = 0;
        for(int i = 0; i < n; ++i) {
            k += arr[i];

            int c = s[i] - 'a';

            if( k >= 0 || c + k >= 0 ) {
                c = (c + k) % 26;
                s[i] = c + 'a';

            } else {
                int q = (c + k) / 26; // q < 0
                int t = (c + k) - 26 * q;
                s[i] = t < 0 ? (26 + t) + 'a' : 'a';

            }
        }

        return s;
    }
};
