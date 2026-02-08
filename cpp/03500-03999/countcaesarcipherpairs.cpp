
// 3805. Count Caesar Cipher Pairs
// https://leetcode.com/problems/count-caesar-cipher-pairs/


class Solution {
public:
    long long countPairs(vector<string>& words) {
        int n = words.size();    // 1 <= n <= 1e5
        if( n == 1 )
            return 0LL;

        int m = words[0].size(); // 1 <= m <= 1e5
        // 1 <= n * m <= 1e5

        // formula number of pairs n * (n-1)/2
        // worst case n = 1e5 => number of pairs 4,999,950,000
        if( m == 1 )
            return (long long)n * ((n-1)/2.0);

        // 01234567890123456789012345
        // abcdefghijklmnopqrstuvwxyza cyclic
        // example "fusion" and "layout" are similar, we can shift "fusion' 6 times and get "layout"
        // "fusion" -> "gvtjpo" -> "hwukqp" -> "ixvlrq" -> "jywmsr" -> "kzxnts" -> "layout"

        // we are after similar word pairs word[i],word[j] with i < j
        // let us create new words as follows (we know at this point m >=2 )
        // we create words with length m-1
        // word_new[i] = word[i] - word[i+1] for 0 <= i < m-1
        // if word[i] > word[i+1] then +26
        // we count the new words and calc number of pairs for each

        unordered_map<string, int> freq;
        for(string& word: words) {
            string word_new = "";
            for(int i = 0; i < m-1; ++i) {
                int c = word[i] - word[i+1];
                if( c < 0 )
                    c += 26;
                word_new.push_back(c+'a');
            }
            ++freq[word_new];
        }

        long long ans = 0;
        for(auto& p: freq)
            ans += (long long)p.second * ((p.second-1)/2.0);

        return ans;
    }
};
