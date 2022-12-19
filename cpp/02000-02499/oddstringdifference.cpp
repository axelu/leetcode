
// 2451. Odd String Difference
// https://leetcode.com/problems/odd-string-difference/


class Solution {
public:
    string oddString(vector<string>& words) {
        // 3 <= words.length <= 100

        int n = words[0].size();

        // difference integer array diff[0] of length n-1
        vector<int> diff0(n-1);
        for(int j = 0; j < n-1; ++j)
            diff0[j] = words[0][j+1] - words[0][j];

        vector<int> diff1(n-1);
        for(int j = 0; j < n-1; ++j)
            diff1[j] = words[1][j+1] - words[1][j];

        // if diff0 == diff1, then we know that if we encounter
        // an integer array different than that, that that is our answer
        if( diff0 == diff1 ) {
            for(int i = 2; i < words.size(); ++i) {
                vector<int> diff(n-1);
                for(int j = 0; j < n-1; ++j)
                    diff[j] = words[i][j+1] - words[i][j];
                if( diff != diff0 )
                    return words[i];
            }
        }

        vector<int> diff2(n-1);
        for(int j = 0; j < n-1; ++j)
            diff2[j] = words[2][j+1] - words[2][j];

        return diff2 == diff0 ? words[1] : words[0];
    }
};
