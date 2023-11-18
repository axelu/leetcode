
// 2901. Longest Unequal Adjacent Groups Subsequence II
// https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-ii/




class Solution {
private:
    bool is_hamming_distance_one(string& s1, string& s2) {
        int n = s1.size(); // s1.size == s2.size
        int cnt = 0;
        for(int i = 0; i < n && cnt <= 1; ++i)
            if( s1[i] != s2[i] )
                ++cnt;
        return cnt == 1;
    }
public:
    vector<string> getWordsInLongestSubsequence(int n, vector<string>& words, vector<int>& groups) {
        if( n == 1 )
            return {words[0]};

        // 1 <= words[i].size() <= 10


        int dp_l[n]; // length of the longest subsequence ending with words[i] that satisfies the conditions
        dp_l[0] = 1;
        int dp_p[n]; // index of prior index in longest subsequence ending with words[i] that satisfies the conditions
        dp_p[0] = -1;

        vector<int> lst[11]; // idx of last word seen with length l
        lst[words[0].size()].push_back(0);

        for(int i = 1; i < n; ++i) {

            int curr_word_lgt = words[i].size(); // current word length
            int curr_word_grp = groups[i];       // current word group

            // traverse all prior words of same length
            //    check if group is different AND if hamming distance is 1
            //    if both conditions are met, keep track of max subsequence length and at what index it occured

            dp_l[i] = 1;
            dp_p[i] = -1;
            for(int k = lst[curr_word_lgt].size()-1; k >= 0; --k) {
                int j = lst[curr_word_lgt][k];
                if( groups[j] != curr_word_grp && is_hamming_distance_one(words[i],words[j]) ) {
                    if( dp_l[j] + 1 > dp_l[i] ) { // TODO consider moving as second check in if
                        dp_l[i] = dp_l[j] + 1;
                        dp_p[i] = j;
                    }
                }
            }

            lst[curr_word_lgt].push_back(i);
        }

        int mx_l = 1;
        int idx = 0;
        for(int i = 1; i < n; ++i) {
            if( dp_l[i] > mx_l ) {
                mx_l = dp_l[i];
                idx = i;
            }
        }

        vector<string> ans;
        while( idx != -1 ) {
            ans.push_back(words[idx]);
            idx = dp_p[idx];
        }
        reverse(begin(ans),end(ans));

        return ans;
    }
};
