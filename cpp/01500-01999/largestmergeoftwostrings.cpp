
// 1754. Largest Merge of Two Strings
// https://leetcode.com/problems/largest-merge-of-two-strings/



class Solution {

public:
    string largestMerge(string& word1, string& word2) {
        int n1 = word1.size();
        int n2 = word2.size();
        string ans = "";
        int p1 = 0, p2 = 0;
        while( p1 != n1 && p2 != n2 ) {
            // greedy
            if( word1[p1] > word2[p2] ) {
                ans.push_back(word1[p1]);
                ++p1;
            } else if( word1[p1] < word2[p2] ) {
                ans.push_back(word2[p2]);
                ++p2;
            } else {
                // word1[p1] == word2[p2]
                // look ahead
                // we need to advance in the word
                // that has the greater remainder
                if( word1.substr(p1) > word2.substr(p2) ) {
                    ans.push_back(word1[p1]);
                    ++p1;
                } else {
                    ans.push_back(word2[p2]);
                    ++p2;
                }
            }
        }

        if( p1 != n1 )
            ans += word1.substr(p1);
        if( p2 != n2 )
            ans += word2.substr(p2);

        return ans;
    }
};
