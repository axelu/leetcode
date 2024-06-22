
// 3029. Minimum Time to Revert Word to Initial State I
// https://leetcode.com/problems/minimum-time-to-revert-word-to-initial-state-i/




class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        int n = word.size();
        if( k == n )
            return 1;

        // worst case
        // if n % k == 0 -> n/k
        // else n/k + 1
        // the question is, can we do better?

        for(int i = k, round = 1; i < n; i += k, ++round) {
            // is word.substr(i) a prefix of word?
            int j = i;
            for(; j < n; ++j)
                if( word[j] != word[j-i] )
                    break;
            if( j == n )
                return round;
        }

        return n % k == 0 ? n/k : n/k + 1;
    }
};
