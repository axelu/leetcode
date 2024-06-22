
// 3023. Find Pattern in Infinite Stream I
// https://leetcode.com/problems/find-pattern-in-infinite-stream-i/





/**
 * Definition for an infinite stream.
 * class InfiniteStream {
 * public:
 *     InfiniteStream(vector<int> bits);
 *     int next();
 * };
 */

// initialize once
long long p_pow[100101];
bool init = false;

class Solution {
public:
    int findPattern(InfiniteStream* stream, vector<int>& pattern) {
        const int p = 31;
        const int m = 1e9 + 9;

        if( !init ) {
            init = true;
            p_pow[0] = 1;
            for (int i = 1; i < 100101; i++)
                p_pow[i] = (p_pow[i-1] * p) % m;
        }

        // calculate hash value of pattern
        int S = pattern.size();
        long long h_s = 0;
        for (int i = 0; i < S; i++)
            h_s = (h_s + (pattern[i] + 1) * p_pow[i]) % m;

        // cout << "h_s " << h_s << endl;

        // build rolling hash from stream as we go along
        long long h[100101];
        h[0] = 0;
        for(int i = 0; i < 100099; ++i) {
            int c = stream->next();
            h[i+1] = (h[i] + (c + 1) * p_pow[i]) % m;

            if( i+1 >= S ) {
                long long cur_h = (h[i+1] + m - h[i+1-S]) % m;
                if (cur_h == h_s * p_pow[i+1-S] % m)
                    return i+1-S;
            }
        }

        // the input is generated such that the pattern's start index exists in the first 1e5 bits of the stream
        // hence we should never get here.
        return -1;
    }
};
