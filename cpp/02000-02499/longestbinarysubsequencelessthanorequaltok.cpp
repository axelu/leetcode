
// 2311. Longest Binary Subsequence Less Than or Equal to K
// https://leetcode.com/problems/longest-binary-subsequence-less-than-or-equal-to-k/





/*                           987654321098765432109876543210
 * decimal 1000000000 binary 111011100110101100101000000000
 *
 */
class Solution {
private:
    string int2string(int x) {
        // 1 <= k <= 10^9
        string s = "000000000000000000000000000000";
        for(int i = 0; i < 30; ++i) {
            if( x & (1 << i) )
                s[29-i] = '1';
        }
        while( !s.empty() && s[0] == '0' ) {
            s.erase(0,1);
        }
        return s;
    }

public:
    int longestSubsequence(string s, int k) {
        int s_sz = s.size();

        string k_str = int2string(k);
        int k_sz = k_str.size();

        // edgecase
        if( s_sz < k_sz )
            return s_sz;

        // for each position in s, record the zero's to its left
        int zeros[s_sz];
        int zeros_cnt = 0;
        for(int i = 0; i < s_sz; ++i) {
            zeros[i] = zeros_cnt;
            if( s[i] == '0' )
                ++zeros_cnt;
        }

        int ans = k_sz - 1;

        // slide the k_str from right to left over s
        for(int i = s_sz - k_sz; i >= 0; --i) {
            int s_idx = i;
            int state = 0; // 0 equal or less, 1 greater
            for(int j = 0; j < k_sz; ++j) { // index in k_str
                if( s[s_idx] == '1' && k_str[j] == '0' ) {
                    state = 1;
                    break;
                } else if( s[s_idx] == '0' && k_str[j] == '1' ) {
                    break;
                }
                ++s_idx;
            }
            if( state == 0 )
                ans = max(ans, zeros[i] + k_sz);
            else
                ans = max(ans, zeros[i] + k_sz - 1);
        }

        return ans;
    }
};
