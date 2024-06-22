
// 3085. Minimum Deletions to Make String K-Special
// https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/






class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int> freq(26, 0);
        for(char c: word)
            ++freq[c-'a'];
        /*
        for(int i = 0; i < 26; ++i)
            cout << (char)(i + 'a') << " " << freq[i] << " ";
        cout << endl;
        */

        for(auto it = freq.begin(); it != freq.end(); ) {
            if( *it == 0 ) {
                it = freq.erase(it);
                continue;
            }
            ++it;
        }

        int n = freq.size(); // 1 <= n <= 26
        if( n == 1 )
            return 0;

        sort(freq.begin(),freq.end());
        /*
        for(int x: freq)
            cout << x << " ";
        cout << endl;
        */
        if( freq[n-1] - freq[0] <= k )
            return 0;

        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + freq[i-1];

        int ans = INT_MAX;

        // sliding window
        int i = 0;
        for(int j = 1; j < n; ++j) {

            int diff = freq[j] - freq[i];
            while( diff > k ) {
                // everything to the left of i needs to be eliminated
                int t = prefixSum[i];
                // AND everything in range [j, n-1] needs to be reduced to freq[i] + k;
                t += (prefixSum[n] - prefixSum[j]) - ((freq[i] + k) * (n-j));

                ans = min(ans, t);
                // cout << "i " << i << " j " << j << " t " << t << " ans " << ans << endl;

                // while( freq[j] - freq[i] > k )
                    ++i;
                diff = freq[j] - freq[i];

            }
        }
        // finish up
        // everything to the left of i needs to be eliminated
        ans = min(ans, prefixSum[i]);

        return ans;
    }
};
