
// 2953. Count Complete Substrings
// https://leetcode.com/problems/count-complete-substrings/





class Solution {
public:
    int countCompleteSubstrings(string word, int k) {
        int n = word.size();
        if( n == 1 )
            return 1;

        int prefixSum[26][n+1];
        for(int i = 0; i < 26; ++i)
            prefixSum[i][0] = 0;
        for(int i = 1; i <= n; ++i) {
            int c = word[i-1]-'a';
            for(int j = 0; j < 26; ++j)
                prefixSum[j][i] = j != c ? prefixSum[j][i-1] : prefixSum[j][i-1] + 1;
        }

        // if there are two adjacent chars, who's absolute difference in their positions in the alphabet > 2,
        // then a 'complete' substring cannot cross that, so we can divide word into intervals

        vector<int> intervals;
        intervals.push_back(0);           // start of interval
        for(int i = 1; i < n; ++i) {
            if( abs((word[i-1]-'a') - (word[i]-'a')) > 2 ) {
                intervals.push_back(i-1); // end of interval
                intervals.push_back(i);   // start of interval
            }
        }
        intervals.push_back(n-1);         // end of interval

        // let l be the length of a given interval
        // our answer lies between k as a minimum (one char occuring k times) and
        // k * x <= l ( the length of a complete substring has to be a multiple of k)
        // also, there are only 26 chars in the alphabet
        // so if k = 1, then our longest window is max 26 before there has to be a repitition of the char
        //    if k = 2, then our longest window is max 52 before there has to be a repitition of the char
        //  k * x <= min(l, k * 26)

        int ans = 0;

        // process interval by interval
        for(int i = 0; i < intervals.size(); i += 2) {
            int interval_start_idx = intervals[i];
            int interval_end_idx   = intervals[i+1];
            int interval_length     = interval_end_idx - interval_start_idx + 1;
            if( interval_length < k )
                continue;

            // cout << "interval_start_idx " << interval_start_idx << " interval_end_idx " << interval_end_idx << " interval_length " << interval_length << endl;


            for(int x = 1; x <= 26 && k * x <= interval_length; ++x) {
                int window_size = x * k;
                // cout << "window_size " << window_size << endl;

                // slide a window of window_size over [start_idx, end_idx - window_size + 1]
                for(int window_start_idx = interval_start_idx; window_start_idx <= interval_end_idx - window_size + 1; ++window_start_idx) {
                    int window_end_idx = window_start_idx + window_size - 1;

                    // cout << "window_start_idx " << window_start_idx << " window_end_idx " << window_end_idx << endl;

                    bool f = true;
                    for(int j = 0; j < 26; ++j) {
                        int cnt = prefixSum[j][window_end_idx+1] - prefixSum[j][window_start_idx];
                        if( cnt > 0 && cnt != k ) {
                            f = false;
                            break;
                        }
                        // TODO if cnt > k then any window going over this range is not good -> optimize
                    }
                    if( f ) {
                        ++ans;
                        // cout << "HIT window_start_idx " << window_start_idx << " window_end_idx " << window_end_idx << endl;
                    }
                }

            }
        }

        return ans;
    }
};
