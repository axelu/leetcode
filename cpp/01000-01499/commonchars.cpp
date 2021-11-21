
// 1002. Find Common Characters
// https://leetcode.com/problems/find-common-characters/


class Solution {
public:
    vector<string> commonChars(vector<string>& A) {
        size_t n = A.size();

        int cnt[n][26];
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < 26; ++j)
                cnt[i][j] = 0;
            for(char c : A[i])
                ++cnt[i][c-'a'];
        }

        vector<string> ans;
        int k;
        for(int j = 0; j < 26; ++j) {
            k = 100;
            for(int i = 0; i < n; ++i) {
                k = min(k,cnt[i][j]);
                if( 0 == k ) break;
            }
            for(; k > 0; --k)
                ans.push_back(string(1,j+'a'));
        }

        return ans;
    }
};
