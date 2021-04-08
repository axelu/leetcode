
// 1668. Maximum Repeating Substring
// https://leetcode.com/problems/maximum-repeating-substring/


class Solution {
public:
    int maxRepeating(string& sequence, string& word) {
        int k = 0;

        size_t n = sequence.size();
        string t = word;
        while( t.size() <= n ) {
            if( sequence.find(t) == string::npos ) break;
            ++k;
            t += word;
        }
        return k;
    }
};
