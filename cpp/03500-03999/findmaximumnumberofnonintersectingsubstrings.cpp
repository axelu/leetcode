
// 3557. Find Maximum Number of Non Intersecting Substrings
// https://leetcode.com/problems/find-maximum-number-of-non-intersecting-substrings/






class Solution {
public:
    int maxSubstrings(string& word) {
        int n = word.size(); // 1 <= word.length <= 2 * 1e5
        if( n < 4 )
            return 0;

        vector<int> positions[26];
        for(int i = 0; i < n; ++i) {
            int c = word[i] - 'a';
            positions[c].push_back(i);
        }

        int next_valid[200000]; memset(next_valid, -1, sizeof next_valid);
        for(int c = 0; c < 26; ++c) {
            int c_cnt = positions[c].size();
            for(int i = 0; i < c_cnt - 1; ++i) {
                // char c occurs at pos positions[i];
                int pos = positions[c][i];

                int next_valid_pos_idx = i+1;
                while( next_valid_pos_idx < c_cnt && positions[c][next_valid_pos_idx] < pos+3 )
                    ++next_valid_pos_idx;
                if( next_valid_pos_idx < c_cnt )
                    next_valid[pos] = positions[c][next_valid_pos_idx];
            }
        }

        /*
        // debug
        for(int i = 0; i < n; ++i)
            cout << i << ":" << next_valid[i] << " ";
        cout << endl;
        */

        // bottom up dp
        int dp[200001];memset(dp, 0, sizeof dp);
        for(int i = n-4; i >= 0; --i) {
            dp[i] = dp[i+1];
            if( next_valid[i] != -1 )
                dp[i] = max(dp[i], 1 + dp[next_valid[i]+1]);
        }

        return dp[0];
    }
};
