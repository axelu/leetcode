
// 2506. Count Pairs Of Similar Strings
// https://leetcode.com/problems/count-pairs-of-similar-strings/


class Solution {
public:
    int similarPairs(vector<string>& words) {
        int n = words.size();
        vector<int> v(n);
        for(int i = 0; i < n; ++i) {
            int t = 0;
            for(char c: words[i])
                t |= 1 << (c-'a');
            v[i] = t;
        }

        int ans = 0;
        for(int i = 0; i < n-1; ++i)
            for(int j = i+1; j < n; ++j)
                if( v[i] == v[j] )
                    ++ans;

        return ans;
    }
};
